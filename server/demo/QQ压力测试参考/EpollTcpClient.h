#ifndef __EPOLLTCPCLIENT_H
#define __EPOLLTCPCLIENT_H

#include "Socket.h"
#include "EpollBase.h"

class CEpollTcpClient : public CEpollBase
{
public:
	CEpollTcpClient();
	~CEpollTcpClient();

	void OnReadData(int fd);
	void Run(int nevent);
	
private:	    
    TCPClient m_tcpclient;  //客户端连接，用于读取数据包
};

#endif 

