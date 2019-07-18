/*************************************************************************
	> File Name: BaseSocket.cpp
	> Author: eric
	> Mail:
	> Created Time: 2017年11月28日 星期二 07时01分47秒
 ************************************************************************/

#include <iostream>
#include "BaseSocket.h"
using namespace std;

CBaseSocket::CBaseSocket()
{
    m_fd = -1;
    m_stream.SetFd(m_fd);
}

CBaseSocket::CBaseSocket(int type, int sin_farmly /* = AF_INET */, int protocol /* = 0 */)
{
    Create(sin_farmly, type, protocol);
}

CBaseSocket::~CBaseSocket()
{
}

void CBaseSocket::Create(int sin_farmly, int flag, int protocl)
{
    m_fd = socket(sin_farmly, flag, protocl);
    if (m_fd < 0)   //当文件描述符达到上限时会创建失败
    {
        perror("create socket error:");
    }
    m_stream.SetFd(m_fd);
}

void CBaseSocket::SetSocket(int fd)
{
    if (m_fd > 0)
    {
        printf("old fd %d will change to %d\n", m_fd, fd);//为何warning
    }
    if (fd < 0)
    {
        printf("set fd %d\n", fd);
    }
    m_fd = fd;
    m_stream.SetFd(m_fd);
}

CHostAddress CBaseSocket::GetAddress()
{
    CHostAddress addr;
    memset(&addr, 0, sizeof(addr));
    if (getsockname(m_fd, addr.Address(), addr.LengthPtr()) != 0)
    {
        perror("getsockname error:");
    }
    return addr;
}

CHostAddress CBaseSocket::GetPeerAddress()
{
    CHostAddress addr;
    memset(&addr, 0, sizeof(addr));
    if (getpeername(m_fd, addr.Address(), addr.LengthPtr()) != 0)
    {
        perror("getpeername error:");
    }
    return addr;
}

bool CBaseSocket::Bind(CHostAddress addr)
{
    int ret = bind(m_fd, addr.Address(), addr.Length());
    if (ret < 0)
    {
        perror(" bind error:");
    }
    return  ret==0 ? true : false;
}

bool CBaseSocket::Close()
{
    if (m_fd < 0)
    {
        printf("close sockfd fd %d\n",m_fd);
        return false;
    }
    int ret = close(m_fd);
    return  ret==0 ? true : false;
}



