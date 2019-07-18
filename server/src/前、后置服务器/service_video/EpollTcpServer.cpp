#include "EpollTcpServer.h"
#include "TcpSocket.h"


CEpollTcpServer::CEpollTcpServer(CHostAddress addr, unsigned int maxEvent,int timeout)
:CEpollBase(maxEvent,timeout)
{
    m_tcpServer.Bind(addr);
    m_tcpServer.Listen(100);
    AddEvent(m_tcpServer.GetSocket(),EPOLLIN);//10086 epoll
}

CEpollTcpServer::~CEpollTcpServer()
{
}

void CEpollTcpServer::Run(int nevent)
{
    for(int i=0;i<nevent;i++)
    {
        if((m_retEvent+i)->data.fd == m_tcpServer.GetSocket())
        {
            OnNewConnection();
        }
        else if((m_retEvent+i)->events & EPOLLIN)
        {
            OnReadData((m_retEvent+i)->data.fd);
        }
    }
}

void CEpollTcpServer::OnNewConnection()
{
    CTcpSocket client=m_tcpServer.Accept();//建立连接
    AddEvent(client.GetSocket(),EPOLLIN);//添加客户端到监听
}

void CEpollTcpServer::OnClientClose(int fd)
{
    DelEvent(fd,EPOLLIN);
    close(fd);
}

//派生类决定OnReadData
//buf
void CEpollTcpServer::OnReadData(int fd)
{
	printf("Client[%d] read event\n",fd);
}
// CEpollTcpServer epollserver(CHostAddress addr("127.0.0.1", 10086));
//epollserver.Start();
//epollserver.Stop();
