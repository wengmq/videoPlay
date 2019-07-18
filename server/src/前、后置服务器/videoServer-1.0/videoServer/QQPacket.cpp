/*************************************************************************
	> File Name: QQPacke.cpp
	> Author: eric
	> Mail: 
	> Created Time: 2017年11月24日 星期五 23时41分03秒
 ************************************************************************/

#include <iostream>
#include <string.h>
#include "QQPacket.h"

using namespace std;

CQQPacket::CQQPacket()
	:CBasePacket(sizeof(packet_all_st))
{
    memset(&m_head, 0, sizeof(m_head));
}

CQQPacket::~CQQPacket()
{
    
}

bool CQQPacket::pack()
{
   memcpy(m_data, &this->m_head, sizeof(packet_header_t));     
   memcpy(m_data+sizeof(packet_header_t), this->m_Body, sizeof(m_Body));
   return true;
}

bool CQQPacket::unpack()
{
   memcpy(&this->m_head, m_data, sizeof(packet_header_t));     
   memcpy(this->m_Body, m_data+sizeof(packet_header_t), sizeof(m_Body));    
   return true;
}

bool CQQPacket::Login_ret(int ret)
{
    //填充包头
    m_head.funid = 0x01; //login
    m_head.optid = 0x00; //登录请求
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;
    
    //填充包体
    Login_ret_t *body = (Login_ret_t*)m_Body;
//    QByteArray qByteArrayName = name.toUtf8();
//    QByteArray qByteArrayPwd = pwd.toUtf8();

//    strcpy(body->usr, name);
  //  strcpy(body->psw, qByteArrayPwd.data());
    body->ret = ret;

    return this->pack();
}


packet_header_t* CQQPacket::getHeader(void)
{
	return &m_head;
}

void* CQQPacket::getBody(void)
{
	return m_Body;
}

void CQQPacket::setFd(int fd)
{
    m_head.fd= fd;
}
int CQQPacket::getFd()
{
    return m_head.fd;
}
