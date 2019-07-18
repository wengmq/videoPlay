#include "BaseThread.h"

CBaseThread::CBaseThread()
:m_bRun(false)
{
	
}

CBaseThread::~CBaseThread()
{
	
}
/*
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
*/

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
void CBaseThread::stop()
{
    m_bRun = false;
}

bool CBaseThread::isRunning() const
{
	return m_bRun;
}

pthread_t CBaseThread::threadId() const
{
	return m_tid;
}

void * CBaseThread::rountine(void *arg)
{	
	pthread_detach(pthread_self());   //自分离线程，不用调用join函数等待
	
	CBaseThread *thr = (CBaseThread *)arg;
	
	thr->m_bRun = true;
	int ret = thr->run();     //用户自定义的处理函数
	thr->m_bRun = false;	
   
	return NULL;
}




















