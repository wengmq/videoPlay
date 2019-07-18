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
	void stop(); //ֹͣ�߳�
	virtual int run() = 0;  //�û��Զ��崦���������������б���ʵ��
	bool isRunning() const;    // ��ȡ�߳����б��
	pthread_t threadId() const;  //��ȡ�߳�id
	
protected:
	pthread_t m_tid;  //�߳�ID
	bool m_bRun;      // ���б��
private:
	static void * rountine(void *arg);   //�߳��ദ�������
};

#endif