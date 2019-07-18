#ifndef EPOLLBASE_H_
#define EPOLLBASE_H_

#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
/*
 1.共同点可以提取成基类，不变

 创建 ，增，改，删，设置定时，等待（epoll_wait）
 2.可变
  int nevent  = epoll_wait之后的处理
  Run
 3.固定的操作
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
	
protected:    //目的是让子类能调用
	int m_maxEvent;  //并发的最大事件
	struct epoll_event *m_retEvent;  //保存描述符事件的数组
	
private:
	int m_epfd;       //epoll监视描述符
	int m_timeout;    //超时时间
	bool m_bStop;     //结束标记
	struct epoll_event m_event;  //用于增加删除等操作
	
};

#endif //_EPOLLBASE_H_

