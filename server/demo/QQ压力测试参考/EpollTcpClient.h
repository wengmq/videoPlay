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
    TCPClient m_tcpclient;  //�ͻ������ӣ����ڶ�ȡ���ݰ�
};

#endif 

