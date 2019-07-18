#ifndef BASESOCKET_H
#define BASESOCKET_H

#pragma once

#include "BaseStream.h"
//基类 socket bind close
class CBaseSocket
{
public:
	CBaseSocket();
	CBaseSocket(int type, int sin_farmly = AF_INET, int protocol = 0); //socket(PF_INET,SOCK_STREAM,0)
	~CBaseSocket();
	int GetSocket() const { return m_fd; }
	void SetSocket(int fd); // 
	CHostAddress GetAddress(void);
    CHostAddress GetPeerAddress(void);
	bool Bind(CHostAddress addr);
	bool Close(void);
protected:
	void Create(int sin_farmly, int flag, int protocl);
	int m_fd;
	CBaseStream m_stream;//文件流的一个对象
};

#endif

