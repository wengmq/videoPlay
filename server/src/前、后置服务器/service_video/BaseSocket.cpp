#include <iostream>
#include "BaseSocket.h"
#include <fcntl.h>

using namespace std;

CBaseSocket::CBaseSocket()
{
    m_fd = -1;
    m_stream.SetFd(m_fd);
}

 CBaseSocket::~CBaseSocket()
 {	 
 }

void CBaseSocket::Create(int sin_farmly, int flag, int protocl)
{
    //创建套接字
    m_fd = socket(sin_farmly,flag,protocl);//socket(AF_INET,SOCK_STREAM,0)
    if(m_fd < 0) //当文件描述符达到上限时会创建失败
    {
        perror("create socket error:");
    }
    
    int on =1;
    //closesocket（一般不会立即关闭而经历TIME_WAIT的过程）后想继续重用该socket：
    if(setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(int))<0)//设置复用
    {     
        perror("setsockopt");
        exit(-1);
    }

    m_stream.SetFd(m_fd);
    
}

CBaseSocket::CBaseSocket( int type,int sin_farmly, int protocol)//socket(AF_INET,SOCK_STREAM,0)
{
    this->Create(sin_farmly,type,protocol);
}

void CBaseSocket::SetSocket(int fd)
{
    if(m_fd > 0)
    {
	//	printf("old fd %d will change to %d\n", m_fd, fd);//为何warning
    }
    if(fd < 0 ||  m_fd != fd)
    {
	//	printf("set fd %d\n", fd);
        m_fd  = fd;
        m_stream.SetFd(m_fd);
        m_stream.SetNonBlock(true);
    }
}

bool CBaseSocket::Bind(CHostAddress addr)
{
    int ret=bind(m_fd,addr.Address(),addr.Length());
    if(ret<0)
    {
        perror("bind");
    }
    return ret==0?true:false;
}



bool CBaseSocket::Close()
{
    if(m_fd<0)
    {
        printf("close sockfd %d",m_fd);
        return false;
    }
    int ret=close(m_fd);
    return ret==0?true:false;
}

CHostAddress CBaseSocket::GetAddress()//获取本地地址
{
    CHostAddress addr;
    memset(&addr,0,sizeof(addr));
    if(getsockname(m_fd,addr.Address(),addr.LengthPtr())!=0)
    {
        perror("getsockname error");
    }
    return addr;
}

CHostAddress CBaseSocket::GetPeerAddress()//获取远程地址
{
    CHostAddress addr;
    memset(&addr,0,sizeof(addr));
    if(getpeername(m_fd,addr.Address(),addr.LengthPtr())!=0)//获取socket的对方地址
    {
        perror("getsockname error");
    }
    return addr;
}
