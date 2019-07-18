#ifndef EPOLLBASE_H_
#define EPOLLBASE_H_

#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
/*
 1.��ͬ�������ȡ�ɻ��࣬����

 ���� �������ģ�ɾ�����ö�ʱ���ȴ���epoll_wait��
 2.�ɱ�
  int nevent  = epoll_wait֮��Ĵ���
  Run
 3.�̶��Ĳ���
  start
  wait
  run
  stop

*/
class CEpollBase
{
public:
	CEpollBase(unsigned int maxEvent = 200, int timeout = -1);
	~CEpollBase();
	bool AddEvent(int fd, unsigned int events);
	bool ModEvent(int fd, unsigned int events);
	bool DelEvent(int fd, unsigned int events);
	void SetTimeout(const int timeout);
	int GetTimeout()const;
	int Wait();
	void Start();
	void Stop();
private:
	virtual void Run(int nevent)=0; 
	
protected:    //Ŀ�����������ܵ���
	int m_maxEvent;  //����������¼�
	struct epoll_event *m_retEvent;  //�����������¼�������
	
private:
	int m_epfd;       //epoll����������
	int m_timeout;    //��ʱʱ��
	bool m_bStop;     //�������
	struct epoll_event m_event;  //��������ɾ���Ȳ���
	
};

#endif //_EPOLLBASE_H_

