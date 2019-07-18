#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "EpollBase.h"

CEpollBase::CEpollBase(unsigned int maxEvent/* = 20*/, int timeout/* = -1*/)
{
	this->m_bStop = false;
	this->m_maxEvent = maxEvent;
	this->m_timeout = timeout;
	this->m_retEvent = new struct epoll_event[maxEvent];
	memset(&this->m_event, 0, sizeof(this->m_event));
	this->m_epfd = epoll_create(this->m_maxEvent);
	if(this->m_epfd < 0)
	{
		perror("epoll create error");
	}
}

CEpollBase::~CEpollBase()
{
    if(m_epfd !=-1)
    {
        close(this->m_epfd);
        m_epfd=-1;
    }
    if(NULL !=this->m_retEvent)
    {
        delete []this->m_retEvent;
        this->m_retEvent=NULL;
    }
}

bool CEpollBase::AddEvent(int fd, unsigned int events)
{
    //this->SetNonBlock(fd, true);
    m_event.events = events | EPOLLET;//设置用于边缘触发 events 操作事件
    m_event.data.fd = fd;//设置用于 events 操作的文件描述符
    int ret = epoll_ctl(m_epfd,EPOLL_CTL_ADD,fd,&m_event);//注册m_event
    if(ret<0)
    {
       perror("epoll add event error");
    }
    return ret == 0 ? true : false;
}

bool CEpollBase::ModEvent(int fd, unsigned int events)
{
    m_event.events=events | EPOLLET;
    m_event.data.fd = fd;
    int ret = epoll_ctl(m_epfd,EPOLL_CTL_MOD,fd,&m_event);
    if(ret<0)
    {
        perror("epoll mod event error");
    }
    return ret==0 ? true : false;
}

bool CEpollBase::DelEvent(int fd, unsigned int events)
{
    m_event.events = events | EPOLLET;
    m_event.data.fd = fd;
    int ret = epoll_ctl(m_epfd,EPOLL_CTL_DEL,fd,&m_event);
    if(ret<0)
    {
       perror("epoll del event error");
    }
    return ret==0 ? true:false;
}

void CEpollBase::SetTimeout(const int timeout)
{  
	this->m_timeout = timeout; 
}

int CEpollBase::GetTimeout() const
{
    return this->m_timeout;
}

int CEpollBase::Wait()
{
    int nevent = epoll_wait(m_epfd, m_retEvent, m_maxEvent, m_timeout*1000);
    if(nevent < 0)
    {
        perror("epoll wait error");
        exit(-1);
    }
    else if(nevent==0)
    {
       // printf("timeout\n");
    }
    return nevent;
}

void CEpollBase::Start()
{
    m_bStop = false;
    while(!m_bStop)
    {
        int nevent = this->Wait();
        if(nevent)
        {
            this->Run(nevent);
        }
    }
}
void CEpollBase::Stop()
{
    m_bStop=true;
}

bool CEpollBase::SetNonBlock(int fd, bool flag)
{
    int opts;
    opts=fcntl(fd,F_GETFL);
    if(opts <0)
    {
        perror("fcntl(sock,GETFL)");
        return false;
    }
    if(flag == true)
        opts|=O_NONBLOCK;
    else
        opts&=~O_NONBLOCK;
    if(fcntl(fd,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        return false;
    }       
    return true;
}
