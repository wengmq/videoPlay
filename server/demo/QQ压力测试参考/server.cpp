
#include "commen.h"
#include "Socket.h"
#include "EpollTcpServer.h"

int  connectnum=0;    //连接总数
int  sendPacknum=0;   //发包总数
int  recvPacknum=0;   //收包总数
int  loginSuccessnum=0;   //登录成功总数
int  loginFailednum=0;    //登录失败总数



int main()
{
	TCPServer server(8001);  
	
	CEpollTcpServer  epollServer(server);

	epollServer.Start();

}

