
#include "commen.h"
#include "Socket.h"
#include "EpollTcpServer.h"

int  connectnum=0;    //��������
int  sendPacknum=0;   //��������
int  recvPacknum=0;   //�հ�����
int  loginSuccessnum=0;   //��¼�ɹ�����
int  loginFailednum=0;    //��¼ʧ������



int main()
{
	TCPServer server(8001);  
	
	CEpollTcpServer  epollServer(server);

	epollServer.Start();

}

