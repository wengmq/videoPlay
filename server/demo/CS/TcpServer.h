#ifndef TCPSERVER_H
#define TCPSERVER_H

#pragma once

#include "BaseSocket.h"
#include "TcpSocket.h"

class CTcpServer : public CBaseSocket
{
public:
	CTcpServer();
	~CTcpServer();
	bool Listen(int backlog);
	CTcpSocket Accept();
private:
	void Create();
};


#endif
