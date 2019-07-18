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
	if (m_bRun == false)	//m_bRunΪ�߳��Ƿ��Ѿ���������
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
	    pthread_detach(pthread_self());   //�Է����̣߳����õ���join�����ȴ�
    }
	
	thr->m_bRun = true;
	thr->run();     //�û��Զ���Ĵ�����
	thr->m_bRun = false;
	
    pthread_exit(NULL);
}




















