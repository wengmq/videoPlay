#include <iostream>
#include "HostAddress.h"

using namespace std;

CHostAddress::CHostAddress()//默认构造
{
    memset(&m_addr,0,sizeof(m_addr));
    m_length = sizeof(m_addr);
    m_addr.sin_family = AF_INET; //internet地址族使用ipv4
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);//自动internet地址使用主机匹配地址，主机字节顺序转换为网络字节顺序
}

CHostAddress::CHostAddress(const char *ip, unsigned short port)//IP和端口 inet_addr  htons
{
    memset(&m_addr,0,sizeof(m_addr));
    m_length = sizeof(m_addr);
    m_addr.sin_family = AF_INET;
    if(ip ==NULL)
        m_addr.sin_addr.s_addr = htonl(INADDR_ANY);//自动internet地址使用主机匹配地址，主机字节顺序转换为网络字节顺序
    else
        m_addr.sin_addr.s_addr = inet_addr(ip);//把一个用数字和点表示IP 地址的字符串转换成一个无符号长整型
    m_addr.sin_port=htons(port);
}

CHostAddress::~CHostAddress()
{
}

void CHostAddress::SetIp(const char *ip)
{
    if(ip==NULL)
        m_addr.sin_addr.s_addr=htonl(INADDR_ANY); //自动internet地址使用主机匹配地址，主机字节顺序转换为网络字节顺序
    else
        m_addr.sin_addr.s_addr=inet_addr(ip); //把一个用数字和点表示IP 地址的字符串转换成一个无符号长整型
}

const char* CHostAddress::GetIp()
{
    return inet_ntoa( m_addr.sin_addr); //把一个in_addr地址值转化为点分IP地址字符串
}

void CHostAddress::SetPort(unsigned short port)
{
    m_addr.sin_port=htons(port); //主机字节顺序转换为网络字节顺序
}

const unsigned short CHostAddress::GetPort()
{
    return ntohs(m_addr.sin_port); //网络字节顺序转换为主机字节顺序
}

struct sockaddr* CHostAddress::Address()
{
    return (struct sockaddr*)&m_addr; //套接字地址结构转换struct sockaddr_in * ->struct sockaddr *
}

sockaddr_in* CHostAddress::InAddress()
{
    return &m_addr;
}

int CHostAddress::Length()
{
    return m_length;//套接字地址结构大小
}

socklen_t* CHostAddress::LengthPtr()
{
    return (socklen_t *)&m_length;//套接字地址结构大小的指针
}


