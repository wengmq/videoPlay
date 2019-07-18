#ifndef BASETHREAD_H_
#define BASETHREAD_H_

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

class CBaseThread
{
public:
	CBaseThread();  //��ʱ��û�д����̣߳�ֻ�������
	~CBaseThread();
	void start(); //�����̲߳������߳�
	virtual int run() = 0;  //�û��Զ��崦���������������б���ʵ��
	
protected:
	pthread_t m_tid;  //�߳�ID
	bool m_bRun;      // ���б��
    bool m_bJoin;    //�Ƿ��ǿɷ����
private:
	static void * rountine(void *arg);   //�߳��ദ�������
};

#endif

