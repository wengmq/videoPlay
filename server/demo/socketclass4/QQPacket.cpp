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

bool CQQPacket::Login()
{
    //填充包头
    m_head.funid = 0x01; //login
    m_head.optid = 0x00; //登录请求
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;
    
    //填充包体
    Login_t *body = (Login_t*)m_Body;
    strcpy(body->usr, "Lilu");
    strcpy(body->psw, "123456");

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


