#include "EpollBase.h"

CEpollBase::CEpollBase(unsigned int maxEvent, int timeout)
:m_maxEvent(maxEvent),
m_retEvent(NULL),
m_timeout(timeout),
m_bStop(false)
{
	memset(&m_event,0,sizeof(m_event));
	m_retEvent=new struct epoll_event[m_maxEvent];  //创建注册事件数组
	m_epfd=epoll_create(100);   // 创建epoll描述符
	if (m_epfd<0)
	{
		perror("epoll create error");
	}
}

CEpollBase::~CEpollBase()
{
	close(m_epfd);  //关闭epoll描述符
	if (m_retEvent!=NULL)
	{
		delete[] m_retEvent;  
	}
}

bool CEpollBase::AddEvent(int fd, unsigned int events/*EPOLLIN*/)
{
	m_event.events=events;
	m_event.data.fd=fd;
	//printf("AddEvent...\n");
	int ret=epoll_ctl(m_epfd, EPOLL_CTL_ADD, fd, &m_event);
	if (ret<0)
	{
		perror("epoll add event error");
	}
	return ret==0 ? true:false;
}

bool CEpollBase::ModEvent(int fd, unsigned int events)
{
	m_event.events=events;
	m_event.data.fd=fd;
	int ret=epoll_ctl(m_epfd, EPOLL_CTL_MOD, fd, &m_event);
	if (ret<0)
	{
		perror("epoll mod event error");
	}
	return ret==0 ? true:false;
}

bool CEpollBase::DelEvent(int fd, unsigned int events)
{
	m_event.events=events;
	m_event.data.fd=fd;
	int ret=epoll_ctl(m_epfd, EPOLL_CTL_DEL, fd, &m_event);
	if (ret<0)
	{
		perror("epoll del event error");
	}
	return ret==0 ? true:false;
}

void CEpollBase::SetTimeout(const int timeout)
{
	m_timeout=timeout;
}

int CEpollBase::GetTimeout()const 
{
	return  m_timeout;
}

int CEpollBase::Wait()
{
	int nevent = epoll_wait(m_epfd, m_retEvent, m_maxEvent, m_timeout);
	if (nevent < 0)
	{
		perror("epoll wait error");
		exit(-1);
	}
	else if (nevent == 0)
	{
		printf("epoll timeout");
	}
	return nevent;
}

void CEpollBase::Start()
{
    m_bStop=false;
	printf(" CEpollBase::Start()  Start ...\n");
	while(!m_bStop)
	{	    
		int nevent=Wait();
		Run(nevent);
	}
	printf(" CEpollBase::Start()  Stop ...\n");
}

void CEpollBase::Stop()
{
	m_bStop=true;
}	









