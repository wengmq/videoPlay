

#include "Socket.h"

#include "EpollTcpClient.h"

extern int  recvPacknum;   //�հ�����
extern int  loginSuccessnum;   //��¼�ɹ�����
extern int  loginFailednum;    //��¼ʧ������
 

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
        //���յ���������Ӧ���
        recvPacknum++;//  ���ܰ�����+1

		//����Ӧ�����¼�ɹ�/ʧ��
		//if(pack.body[28]=='1')
		//	loginSuccessnum++;
		//else
		//	loginFailednum++;
    }

}




