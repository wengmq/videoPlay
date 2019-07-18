

#include "Socket.h"

#include "EpollTcpServer.h"

//#include <QDebug>

CEpollTcpServer::CEpollTcpServer(TCPServer& tcpServer)
{
	m_tcpServer = tcpServer;  //服务器对象拷贝

    int listenfd = m_tcpServer.getfd();
    if(listenfd <= 0)
	{
	    perror("EpollTcpServer create error");
        exit(-1);
	}
	AddEvent(listenfd,EPOLLIN);
}

CEpollTcpServer::~CEpollTcpServer()
{
	
}

void CEpollTcpServer::Run(int nevent)
{
	for (int i = 0; i < nevent; i++)
	{   
		if (   (m_retEvent[i].data.fd==m_tcpServer.getfd())
			 && (m_retEvent[i].events & EPOLLIN)             )
		{
			OnNewConnection();
			
		}
		else if (m_retEvent[i].events & EPOLLIN)
		{
			OnReadData(m_retEvent[i].data.fd);
		}
	}
	
}

void CEpollTcpServer::OnNewConnection()
{     
    printf("OnNewConnection \n");
	int fd = m_tcpServer.accept();
	AddEvent(fd, EPOLLIN);
}

void CEpollTcpServer::OnReadData(int fd)
{
	Packet pack={{0},{0}};
    m_tcpclient.m_sockfd = fd;
	
	int nread = m_tcpclient.receive(&pack);
	if (nread == -1)
	{
		perror("read error:");
		DelEvent(fd, EPOLLIN);
		close(fd);		
	}
	else if (nread == 0)
	{
		printf("client close.\n");
		DelEvent(fd, EPOLLIN);
		close(fd);		  
	}
	else
	{
	    //检查数据库中的用户名和密码
		//printf("[%d] read message is : %s\n",fd,pack.body);
		//发送应答包		
		m_tcpclient.send(&pack);
	}

}


void CEpollTcpServer::OnClientClose(int fd)
{
	DelEvent(fd,EPOLLIN);
	close(fd);
}




