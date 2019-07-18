#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>  // semaphore
#include <sys/shm.h> // shared memory
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>  
#include <semaphore.h> 
#include "ShmFIFO.h"

#define ERR_EXIT(m) \
	do{ \
			perror(m); \
			fprintf(stderr, "Err: (%s:%s:%d)", __FILE__, __func__, __LINE__); \
	}while(0)


typedef struct shmhead_st
{
	int shmid;					// // 共享内存ID

	unsigned int blksize;		// 块大小
	unsigned int blocks;		// 总块数
	unsigned int rd_index;		// 读索引
	unsigned int wr_index;		// 写索引

	//必须放在共享内存内部才行
	sem_t sem_rmutex;			// 用来互斥用的信号量
	sem_t sem_wmutex;			// 用来互斥用的信号量
	sem_t sem_full;				// 用来控制共享内存是否满的信号量
	sem_t sem_empty;			// 用来控制共享内存是否空的信号量

}shmhead_t;


		
//此时还没有创建共享类对象
CShmFIFO::CShmFIFO():m_open(false),m_shmhead(NULL),m_payload(NULL)
{
}
	
CShmFIFO::CShmFIFO(int key, int blksize, int blocks)
{
	this->open( key,  blksize,  blocks);
}

CShmFIFO::~CShmFIFO()
{
	this->close();
}
		
bool CShmFIFO:: init(int key, int blksize, int blocks)
{
	int shmid = 0;
	
	//1.查看是否已经存在共享内存，如果有则删除旧的
	shmid = shmget((key_t)key,0,0);
	if(shmid != -1)
	{
		shmctl(shmid, IPC_RMID, NULL);//删除已存在的内存
	}
	//2.创建共享内存返回头地址
	shmid = shmget((key_t)key, sizeof(shmhead_t) + blocks*blksize, 0666| IPC_CREAT | IPC_EXCL);
	if(shmid == -1)
	{
		ERR_EXIT("shmget");
	}
	printf("Create shmid=%d, size=%lu \n", shmid, sizeof(shmhead_t) + blocks*blksize);
	
	//3.链接共享内存
	m_shmhead =shmat(shmid,(void *)0,0);
	if(m_shmhead == (void *)-1)
	{
		ERR_EXIT("shmat");
	}
	memset(m_shmhead, 0, sizeof(shmhead_t) + blocks*blksize);//初始化
		
	//4.初始化共享内存信息
	shmhead_t *pHead = (shmhead_t*)(m_shmhead);
	pHead-> shmid = shmid; //共享内存shmid
	pHead-> blksize = blksize;//共享信息写入
	pHead-> blocks = blocks;//写入每块大小
	pHead-> rd_index = 0;//一开始位置都是第一块
	pHead-> wr_index = 0;
	sem_init(&pHead->sem_wmutex,1,1);//第一个1表示可以跨进程共享，第2个1表示初始化值
	sem_init(&pHead->sem_rmutex,1,1);//第一个1表示可以跨进程共享，第2个1表示初始化值
	sem_init(&pHead->sem_empty,1,0);//第一个1表示可以跨进程共享，第2个0表示初始化值
	sem_init(&pHead->sem_full,1,blocks);//第一个1表示可以跨进程共享，第2个表示初始化值
	
	//5.填充控制共享内存的信息
	m_payload = (char*)(pHead + 1);//实际负载起始位置
	m_open = true;
	
	return true;
}

void CShmFIFO::destroy(void)
{
	shmhead_t *pHead = (shmhead_t *)m_shmhead;
	int shmid = pHead->shmid;
	
	//删除信号量
	sem_destroy(&pHead->sem_full);
	sem_destroy(&pHead->sem_empty);
	sem_destroy(&pHead->sem_wmutex);
	sem_destroy(&pHead->sem_rmutex);
	shmdt(m_shmhead);//共享内存脱离
	
	//销毁共享内存
	if(shmctl(shmid, IPC_RMID, 0) == -1)
	{
		printf("Delete shmid=%d \n", shmid);
		ERR_EXIT("shmctl rm");
	}
	
	m_shmhead =NULL;
	m_payload =NULL;
	m_open = false;
}

void CShmFIFO:: Destroy(int key)//静态删除共享内存方法
{
	int shmid =0;
	
	//1.查看是否已经存在共享内存，如果有则删除
	shmid = shmget((key_t)key,0,0);
	if(shmid != -1)
	{
		shmctl(shmid, IPC_RMID, NULL);//删除已存在的内存
	}
}

bool CShmFIFO:: open(int key, int blksize, int blocks)
{
	int shmid;
	this->close();	
	
	//1.查看是否已经存在共享内存，如果有则删除旧的
	shmid = shmget((key_t)key,0,0);
	if(shmid == -1)//不存在
	{
		return this->init(key, blksize, blocks);
	}
	
	//2.链接共享内存
	m_shmhead = shmat(shmid, (void*)0, 0);
	if(m_shmhead == (void*)-1)
	{
		ERR_EXIT("shmat");
	}
	//3.填充控制共享内存的信息
	m_payload = (char*)((shmhead_t*)m_shmhead + 1 );//实际负载起始位置
	m_open = true;
	
	return true;
}

void CShmFIFO::close(void)
{
	if(m_open)
	{
		shmdt(m_shmhead);//共享内存脱离
		m_shmhead =NULL;
		m_payload =NULL;
		m_open = false;
	}
}

void CShmFIFO::write(const void *buf)
{
	shmhead_t *pHead = (shmhead_t*)m_shmhead;
	
	sem_wait(&pHead->sem_full);//是否有资源写？可用写资源-1
	sem_wait(&pHead->sem_wmutex); //是否有人在写?
	
	memcpy(m_payload + (pHead->wr_index) * (pHead->blksize),buf,pHead->blksize);
	pHead->wr_index =(1+pHead->wr_index) % (pHead->blocks);//写位置偏移
	sem_post(&pHead->sem_wmutex);//解除互斥
	sem_post(&pHead->sem_empty); //可用读资源+1	
}
void CShmFIFO::write(const void *buf,int buf_len)
{
	shmhead_t *pHead = (shmhead_t*)m_shmhead;
	
	sem_wait(&pHead->sem_full);//是否有资源写？可用写资源-1
	sem_wait(&pHead->sem_wmutex); //是否有人在写?
	
	memcpy(m_payload + (pHead->wr_index) * (pHead->blksize),buf,buf_len);
	pHead->wr_index =(1+pHead->wr_index) % (pHead->blocks);//写位置偏移
	sem_post(&pHead->sem_wmutex);//解除互斥
	sem_post(&pHead->sem_empty); //可用读资源+1	
}
void CShmFIFO::read(void *buf)
{
	shmhead_t *pHead =(shmhead_t*) m_shmhead;
	
	sem_wait(&pHead->sem_empty);//检测写资源是否可用
	sem_wait(&pHead->sem_rmutex);
	//printf("read from shm[%d] index %d\n", pHead->shmid, pHead->rd_index);
	memcpy(buf, m_payload + (pHead->rd_index) * (pHead-> blksize),pHead->blksize);
	
	//读位置偏移
	pHead->rd_index = (1+pHead->rd_index) % (pHead->blocks);
	sem_post(&pHead->sem_rmutex);//解除互斥
	sem_post(&pHead->sem_full); //可写资源+1	
}
void CShmFIFO::read(CPacket &buf)
{
	char * p;
	shmhead_t *pHead =(shmhead_t*) m_shmhead;
	
	sem_wait(&pHead->sem_empty);//检测写资源是否可用
	sem_wait(&pHead->sem_rmutex);
	//printf("read from shm[%d] index %d\n", pHead->shmid, pHead->rd_index);
	//memcpy(buf, (m_payload + (pHead->rd_index) * (pHead-> blksize)),pHead->blksize);
	p=(m_payload + (pHead->rd_index) * (pHead-> blksize));
	memcpy(buf.getHeader(),p,sizeof(packet_header_t));
	buf.setSize(sizeof(packet_header_t)+buf.getHeader()->usrlenth+sizeof(packet_tali_st));
	buf.detbody();
    buf.setBodysize(buf.getHeader()->usrlenth);
    p+=sizeof(packet_header_t);
    memcpy(buf.getBody(),p,buf.getHeader()->usrlenth);
    p+=buf.getHeader()->usrlenth;
    memcpy(buf.getTali(),p,sizeof(packet_tali_st));
	//读位置偏移
	pHead->rd_index = (1+pHead->rd_index) % (pHead->blocks);
	sem_post(&pHead->sem_rmutex);//解除互斥
	sem_post(&pHead->sem_full); //可写资源+1	
}


