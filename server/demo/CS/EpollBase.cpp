#include "EpollBase.h"

CEpollBase::CEpollBase(unsigned int maxEvent /* = 20 */, int timeout /* = -1 */)
{
	this->m_bStop = false;
	this->m_maxEvent = maxEvent;
	this->m_timeout = timeout;
    memset(&this->m_event,0,sizeof(this->m_event));
    this->m_retEvent= new struct epoll_event[this->m_maxEvent];//m_retEvent + 3
    this->m_epfd = epoll_create(this->m_maxEvent);
    if (this->m_epfd < 0)
    {
        perror("epoll create error");
    }
}

CEpollBase::~CEpollBase()
{
    if(m_epfd != -1)
        close(this->m_epfd);
    if (this->m_retEvent != NULL)
    {
        delete[] this->m_retEvent;
    }
}

bool CEpollBase::AddEvent(int fd, unsigned int events/*EPOLLIN*/)
{
    this->m_event.events = events;
    this->m_event.data.fd = fd;
    int ret = epoll_ctl(this->m_epfd, EPOLL_CTL_ADD, fd, &this->m_event);
    if (ret < 0)
    {
        perror("epoll add event error");
    }
    return ret==0 ? true:false;
}

bool CEpollBase::ModEvent(int fd, unsigned int events)
{
    this->m_event.events = events;
    this->m_event.data.fd = fd;
    int ret = epoll_ctl(this->m_epfd, EPOLL_CTL_MOD, fd, &this->m_event);
    if (ret < 0)
    {
        perror("epoll mod event error");
    }
    return ret==0 ? true:false;
}

bool CEpollBase::DelEvent(int fd, unsigned int events)
{
    this->m_event.events = events;
    this->m_event.data.fd = fd;
    int ret = epoll_ctl(this->m_epfd, EPOLL_CTL_DEL, fd, &this->m_event);
    if (ret < 0)
    {
        perror("epoll del event error");
    }
    return ret==0 ? true:false;
}
/*SetTimeout 
 * 功能设置epoll 时间事件
 *参数timeout 取值
 *1、-1阻塞 代表 
 *2、=0立即返回
 *3、>0 指定微秒
 autour：yzj  date:2017-5-18
 */
void CEpollBase::SetTimeout(const int timeout)
{
    this->m_timeout = timeout;
}

int CEpollBase::GetTimeout()const
{
    return  this->m_timeout;
}

int CEpollBase::Wait()
{
    int nevent = epoll_wait(this->m_epfd, this->m_retEvent, this->m_maxEvent, this->m_timeout*1000);
    if (nevent < 0)
    {
        perror("epoll wait error");
        exit(-1);
    }
    else if (nevent == 0)
    {
        printf("timeout\n");
    }
    return nevent;
}

void CEpollBase::Start()
{
    this->m_bStop = false;
    while (!this->m_bStop)
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
    this->m_bStop = true;
}









