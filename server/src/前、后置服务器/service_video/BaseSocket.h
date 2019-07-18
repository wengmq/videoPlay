#ifndef BASESOCKET_H
#define BASESOCKET_H

#pragma once

#include "BaseStream.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/epoll.h>
//基类 socket bind close
class CBaseSocket
{
public:
    CBaseSocket();
    CBaseSocket(int type, int sin_farmly = AF_INET, int protocol = 0); //socket(AF_INET,SOCK_STREAM,0) //AF_INET:IPv4 网络协议的套接字类型
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

