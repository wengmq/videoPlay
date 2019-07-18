#include "BaseThread.h"

CBaseThread::CBaseThread()
:m_bRun(false), m_bJoin(false)
{
	
}

CBaseThread::~CBaseThread()
{
	
}

void CBaseThread::start()
{
	if (m_bRun == false)	//m_bRun为线程是否已经在运行了
	{
		if( pthread_create(&m_tid,NULL,rountine,(void *)this) != 0)
		{
			perror("create thread error : ");
		}
		
	}
}

void * CBaseThread::rountine(void *arg)
{	
	CBaseThread *thr = (CBaseThread *)arg;
    if(thr->m_bJoin) {
	    pthread_detach(pthread_self());   //自分离线程，不用调用join函数等待
    }
	
	thr->m_bRun = true;
	thr->run();     //用户自定义的处理函数
	thr->m_bRun = false;
	
    pthread_exit(NULL);
}




















