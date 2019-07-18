#include "BaseThread.h"
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <signal.h>

//此时还没有创建线程，只有类对象
CBaseThread::CBaseThread():
    m_bRun(false),m_bDetach(true),m_name("Thread")
{
}

CBaseThread::CBaseThread(bool detachable):
    m_bRun(false),m_bDetach(detachable),m_name("Thread")
{
}

CBaseThread::~CBaseThread()
{
    join();//阻塞等待退出
}

//创建线程并启动线程
void CBaseThread::start()
{
    if(m_bRun == false)//m_bRun为线程是否已经在运行了
    {
        if(pthread_create(&m_tid,NULL,rountine,(void *)this)!=0)
        {
            perror("create thread error:");//创建失败
        }
	}
}

//线程类处理函数框架
void * CBaseThread::rountine(void *arg)
{
    CBaseThread * thr=(CBaseThread *)arg;
    if(thr->m_bDetach)
    {
        pthread_detach(pthread_self());//自分离线程，不用调用join函数等待
    }
    thr->setName();
    thr->m_bRun=true;
    thr->run();  			 //用户自定义的处理函数
    thr->m_bRun=false;
    
    pthread_exit(NULL);
}

//不分离线程回收
void CBaseThread::join()
{
    m_bRun=false; //exit thread
	// 等待线程pthread释放
    if(m_bDetach == false)
    {
        if(pthread_join(m_tid,NULL)!=0)
        {
            perror("pthread_join error");
        }
    }
    m_tid=-1;
}

void CBaseThread::setName(const char *acName)
{
    if(!acName)
        m_name="Thread";
    else
        m_name=acName;
}

void CBaseThread::setName(void)
{
    char acThreadName[128]={0};
    snprintf(acThreadName,sizeof(acThreadName),"%s(%ld)",m_name,syscall(SYS_gettid));
    prctl(PR_SET_NAME,acThreadName,0,0,0);//用于线程重命名
}





