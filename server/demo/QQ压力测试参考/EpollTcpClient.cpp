

#include "Socket.h"

#include "EpollTcpClient.h"

extern int  recvPacknum;   //收包总数
extern int  loginSuccessnum;   //登录成功总数
extern int  loginFailednum;    //登录失败总数
 

CEpollTcpClient::CEpollTcpClient(){};
CEpollTcpClient::~CEpollTcpClient(){};

void CEpollTcpClient::Run(int nevent)
{
	for (int i = 0; i < nevent; i++)
	{   
		if (m_retEvent[i].events & EPOLLIN)
		{
			OnReadData(m_retEvent[i].data.fd);
		}
	}
	
}

void CEpollTcpClient::OnReadData(int fd)
{
    Packet pack={{0},{0}};
	m_tcpclient.m_sockfd = fd;

	int nread = m_tcpclient.receive(&pack);
	//printf("nread=%d\n",nread);
    if (nread == -1)
    {
        perror("read error:");
		DelEvent(fd, EPOLLIN);
        close(fd);		
    }
    else if (nread == 0)
    {
        printf("client close.\n");
		DelEvent(fd, EPOLLIN);
        close(fd);        
    }
    else
    {
        //printf("read message is : %s  pack.body[28]=%c\n",pack.body,pack.body[28]);
        //接收到服务器的应答包
        recvPacknum++;//  接受包总数+1

		//解析应答包登录成功/失败
		//if(pack.body[28]=='1')
		//	loginSuccessnum++;
		//else
		//	loginFailednum++;
    }

}




