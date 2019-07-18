#ifndef BASESTREAM_H
#define BASESTREAM_H

#pragma once

#include "HostAddress.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

//基本文件流操作
class CBaseStream
{
public:
	CBaseStream();
	CBaseStream(int fd);//普通构造传一个FD
	virtual ~CBaseStream(void);
	
	void SetFd(int fd);
	int GetFd() const;
	bool SetNonBlock(bool flag);
	virtual int Read(char *buf, const int buf_len); //TCP
	virtual int Read(char *buf, const int buf_len, struct timeval *tv/*int timeout == -1*/);//超时
	virtual int Read(char *buf, const int buf_len, CHostAddress &remote_addr);//UDP
	virtual int Read(char *buf, const int buf_len, CHostAddress &remote_addr, struct timeval *tv);//udp超时
	virtual int Write(const char *buf, const int buf_len);
	virtual int Write(const char *buf, const int buf_len, struct timeval *tv);
	virtual int Write(const char *buf, const int buf_len, CHostAddress remote_addr);
	virtual int Write(const char *buf, const int buf_len, CHostAddress remote_addr, struct timeval *tv);
	
	// other API
	virtual int Readn(char *buf, const int buf_len);
	virtual int Writen(const char *buf, const int buf_len);
private:
	int m_fd;
};

#endif
