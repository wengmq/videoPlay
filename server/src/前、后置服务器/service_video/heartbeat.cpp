#include "heartbeat.h"

Cheartbeat::Cheartbeat(CVideoEpollTcpServer * epoll)
{
	m_epoll=epoll;
}
Cheartbeat::~Cheartbeat()
{
}
int Cheartbeat::run(void) 
{
    CTcpSocket clinet;
	//thread while(1)
    while(m_epoll->hstop)
    {
    	m_epoll->setTimeMonit(30);//30 second timeout 
        sleep(20);
    }
    return 0;
}
