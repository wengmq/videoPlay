/*************************************************************************
	> File Name: QQPacke.h
	> Author: eric
	> Mail: 
	> Created Time: 2017年11月24日 星期五 23时39分07秒
 ************************************************************************/

#ifndef _QQPACKE_H
#define _QQPACKE_H
#include "BasePacket.h"
#include "QQpublic.h"

class CQQPacket: public CBasePacket
{
public:
	CQQPacket();
	~CQQPacket();
	bool pack();
	bool unpack();
        bool Login_ret(int ret);

	packet_header_t* getHeader(void);
	void* getBody(void);
        void setFd(int fd);
        int getFd();
//private:
    packet_header_t m_head;
    char m_Body[sizeof(packet_all_st) - sizeof(packet_header_t)];

};

#endif
