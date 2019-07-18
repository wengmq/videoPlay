#ifndef __EPOLLTCPSERVER_H
#define __EPOLLTCPSERVER_H

#include "Socket.h"

#include "EpollBase.h"

class CEpollTcpServer : public CEpollBase
{
public:
	CEpollTcpServer(TCPServer& tcpServer);
	~CEpollTcpServer();

	void OnReadData(int fd/*, char *buf, int bufLen*/);
	void OnNewConnection();
	void OnClientClose(int fd);
	void Run(int nevent);
	
private:	

	TCPServer m_tcpServer;  // 关联的服务器对象，目的是获得监听描述符	
    TCPClient m_tcpclient;  //客户端连接，用于读取数据包
};

#endif //_EPOLLTCPSERVER_H_

