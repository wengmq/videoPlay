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

	TCPServer m_tcpServer;  // �����ķ���������Ŀ���ǻ�ü���������	
    TCPClient m_tcpclient;  //�ͻ������ӣ����ڶ�ȡ���ݰ�
};

#endif //_EPOLLTCPSERVER_H_

