#ifndef BASETHREAD_H_
#define BASETHREAD_H_

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

class CBaseThread
{
public:
	CBaseThread();  //��ʱ��û�д����̣߳�ֻ�������
	CBaseThread(bool detachable);
	virtual ~CBaseThread();
	void start(); //�����̲߳������߳�
	void join();//�������̻߳���
	void setName(const char * acName);
	virtual int run() = 0;  //�û��Զ��崦���������������б���ʵ��
	
protected:
	pthread_t m_tid;  //�߳�ID
	bool m_bRun;      // ���б��
	bool m_bDetach;  //�Ƿ����
	const char * m_name;// �߳�����
private:
	void setName(void);
	static void * rountine(void *arg);   //�߳��ദ�������
};

#endif
