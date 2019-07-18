#ifndef SHMFIFO_H
#define SHMFIFO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h> // shared memory
#include <sys/sem.h>  // semaphore
#include <string.h>
#include <semaphore.h>
#include "VideoSeederPacke.h"
class CShmFIFO
{
public:
    CShmFIFO(int key,int blksize,int blocks);
    CShmFIFO();
    virtual ~CShmFIFO();
	//创建和销毁
    bool init(int key ,int blksize,int blocks);
    void destroy(void);
    static void Destroy(int key);//静态删除共享内存方法

    bool open(int key ,int blksize,int blocks);
    void close(void);
	//读取和存储
    void write(const void * buf);
    void write(const void *buf,int buf_len);
    void read(void * buf);
    void read(CPacket &buf);
protected:
	//进程控制信息块
	bool m_open;
	void *m_shmhead; // 共享内存头部指针
	char *m_payload;// 有效负载的起始地址
};

#endif // SHMFIFO_H
