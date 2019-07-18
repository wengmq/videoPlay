#include "BaseStream.h"
#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

CBaseStream::CBaseStream()
{
}

CBaseStream::CBaseStream(int fd)
{
	 m_fd = fd;
}

CBaseStream::~CBaseStream()
{
  //  close(m_fd);
}

void CBaseStream::SetFd(int fd)
{
	m_fd=fd;
}

int CBaseStream::GetFd() const
{
    return m_fd;
}

bool CBaseStream::SetNonBlock(bool flag)
{
    /*
        fcntl函数有5种功能：
        1.复制一个现有的描述符（cmd=F_DUPFD）.
        2.获得／设置文件描述符标记(cmd=F_GETFD或F_SETFD).
        3.获得／设置文件状态标记(cmd=F_GETFL或F_SETFL).
        4.获得／设置异步I/O所有权(cmd=F_GETOWN或F_SETOWN).
        5.获得／设置记录锁(cmd=F_GETLK,F_SETLK或F_SETLKW).
    */
    int opts;
    opts=fcntl(m_fd,F_GETFL);//获取文件的flags，即open函数的第二个参数:
    if(opts < 0)
    {
        perror("fcntl(sock,F_GETFL)");
        return false;
    }

    if(flag==true)// 设置为非阻塞
        opts|=O_NONBLOCK;
    else
        opts&=~O_NONBLOCK;

    if(fcntl(m_fd, F_SETFL, opts)<0)
    {
        perror("fcntl(sock,SETFL,OPTS)");
        return false;
    }
    return true;
}

int CBaseStream::Read(char *buf, const int buf_len)
{
    int rsize=read(m_fd, buf, buf_len);
    if( rsize< 0)
    {
        perror("read ");
    }
    return rsize;
}

int CBaseStream::Read(char *buf, const int buf_len, struct timeval *tv)
{
    fd_set rfds;//long类型的数组
	FD_ZERO(&rfds);//将指定的文件描述符集清空(必要的)
	FD_SET(m_fd, &rfds);//用于在文件描述符集合中增加一个新的文件描述符m_fd
	switch(select(m_fd +1, &rfds, NULL, NULL, tv))//检查套节字是否可读
	{
		case 0 :
			printf("select timeout!\n");
			return 0;
		case -1:
			perror("select");
			return -1;
		default:
			if(FD_ISSET(m_fd, &rfds))//用于测试指定的文件描述符是否在该集合中。  
									//select将更新这个集合,把其中不可读的套节字去掉   
								  //只保留符合条件的套节字在这个集合里面
								//如果有输入，从stdin中获取输入字符 
				return Read(buf, buf_len);
			else
				return -1;
	}
	return 0;
}

int CBaseStream::Read(char *buf, const int buf_len, CHostAddress &remote_addr)
{
    int rsize =recvfrom(m_fd,buf,buf_len,0,remote_addr.Address(),remote_addr.LengthPtr());
    if(rsize<0)
    {
        perror("recvfrom");
    }
    return rsize;
}

int CBaseStream::Read(char *buf, const int buf_len, CHostAddress &remote_addr, struct timeval *tv)
{
	fd_set rfds; //long类型的数组
	FD_ZERO(&rfds);//将指定的文件描述符集清空(必要的)
	FD_SET(m_fd, &rfds);//用于在文件描述符集合中增加一个新的文件描述符m_fd
	switch(select(m_fd +1, &rfds, NULL, NULL, tv))//检查套节字是否可读, 是否超时
	{
		case 0 :
			printf("select timeout!\n");
			return 0;
		case -1:
			perror("select");
			return -1;
		default:
			if(FD_ISSET(m_fd, &rfds))//用于测试指定的文件描述符是否在该集合中。  
				return Read(buf, buf_len, remote_addr);
			else
				return -1;
	}
}

int CBaseStream::Write(const char *buf, const int buf_len)
{
    int wdsize = write(m_fd, buf, buf_len);
	if(wdsize <= 0)
	{
		perror("send data error:");
	}
	return wdsize;
}

int CBaseStream::Write(const char *buf, const int buf_len, struct timeval *tv)
{
   fd_set wfds;
	FD_ZERO(&wfds);//将指定的文件描述符集清空(必要的)
	FD_SET(m_fd, &wfds);//用于在文件描述符集合中增加一个新的文件描述符
	
	switch(select(m_fd +1, &wfds, NULL, NULL, tv))//检查套节字是否可读, 是否超时
	{
		default:
			if(FD_ISSET(m_fd, &wfds))//用于测试指定的文件描述符是否在该集合中。  
				return Write(buf, buf_len);
			else
				return -1;
		case 0 :
			printf("select timeout!\n");
			return 0;
		case -1:
			perror("select");
			return -1;
	}	
}

int CBaseStream::Write(const char *buf, const int buf_len, CHostAddress remote_addr)
{
    int wdsize = sendto(m_fd, buf, buf_len, 0, remote_addr.Address(),remote_addr.Length());
	if(wdsize <= 0)
	{
		perror("sendto data error:");
	}
	return wdsize;
}

int CBaseStream::Write(const char *buf, const int buf_len, CHostAddress remote_addr,struct  timeval *tv)
{
    fd_set wfds;
	FD_ZERO(&wfds);//将指定的文件描述符集清空(必要的)
	FD_SET(m_fd, &wfds);//用于在文件描述符集合中增加一个新的文件描述符
	
	switch(select(m_fd +1, &wfds, NULL, NULL, tv))//检查套节字是否可读, 是否超时
	{
		default:
			if(FD_ISSET(m_fd, &wfds))//用于测试指定的文件描述符是否在该集合中。  
				return Write(buf, buf_len, remote_addr);
			else
				return -1;
		case 0 :
			printf("select timeout!\n");
			return 0;
		case -1:
			perror("select");
			return -1;
	}	
	return 0;
}
// other API
//server读取数据
int CBaseStream::Readn(char *buf, const int buf_len)//读取真实数据
{
    int nLeft = buf_len;//剩余字节流
	int nRead = 0;//用于返回值
	char *pBuf = (char *)buf;
	
	while(nLeft >0)
	{
		nRead = ::read(m_fd, pBuf, nLeft);//发送数据
        if( nRead < 0)
        {
            if(errno == EINTR)//被异常中断信号打断
                continue;
            else
           		 return -1 ; //err
        }
		if( nRead == 0)//读完
        {
            return (buf_len - nLeft) ;
        }
		else
		{
			nLeft = nLeft - nRead;//剩余字符数
			pBuf = pBuf + nRead;//下次的偏移位置
		}
	}	 
	return buf_len;
}

//client向server写数据
int CBaseStream::Writen(const char *buf, const int buf_len)
{
   int nLeft = buf_len;//剩余字节流
	int nWritten = 0;//return 
	char *pBuf = (char *)buf;
	
	while(nLeft > 0)
	{
		nWritten = ::write(m_fd, pBuf, nLeft);//写数据
		if( nWritten < 0)//err
		{
			if(errno == EINTR)//异常中断
				continue;
			else			 //Err
				return -1;
		}
		else if(nWritten == 0)
			continue;
		else
		{
			nLeft -= nWritten;//剩余字节流
			pBuf += nWritten;//偏移位置
		}	
	}
	return buf_len;	
}


