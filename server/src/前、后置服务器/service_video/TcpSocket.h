#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#pragma once
#include "BaseSocket.h"
#include "HostAddress.h"
//�ͻ���TCP  socket ʵ�ֻ���Create �Լ����� connect
class CTcpSocket :public CBaseSocket//�̳���socket����
{
public:
	CTcpSocket(void);
	CTcpSocket(const CTcpSocket &other);
	CTcpSocket(int fd);
	virtual ~CTcpSocket(void);
	
	CTcpSocket& operator = (const CTcpSocket &other);
	CHostAddress GetRemoteAddr() const;
	void SetRemoteAddr(const CHostAddress remote_addr);
	bool Connect(CHostAddress addr);
	void setID(int &id);
	int  getID();

	int Read(char *buf, const int buf_len);
	int Read(char *buf, const int buf_len, struct timeval *tv);
	int Readn(char *buf, const int buf_len);
	int Write(char *buf, const int buf_len);
	int Write(char *buf, const int buf_len, struct timeval *tv);
	int Writen(char *buf, const int buf_len);
protected:
	int user_id;
	char username[20];
	void Create();
	CHostAddress m_remote_addr; //�Է������ӵ�ַ��
};


#endif
