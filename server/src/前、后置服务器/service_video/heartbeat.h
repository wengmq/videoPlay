#ifndef Cheartbeat_H
#define Cheartbeat_H

#include "BaseThread.h"
#include "CVideoEpollTcpServer.h"
//qq回包的线程
class Cheartbeat:public CBaseThread
{
public:

    Cheartbeat(CVideoEpollTcpServer * epoll);
    ~Cheartbeat();
	
    int run(void);
private:
   CVideoEpollTcpServer * m_epoll;
};

#endif // Cheartbeat_H
