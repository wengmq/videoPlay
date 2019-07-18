
#include "QQEpollTcpServer.h"


/*使用epoll模型接收多客户端数据，并应答*/
int main()
{
	CHostAddress addr(NULL, 10086);
	CQQEpollTcpServer epollsever(addr);
	epollsever.Start();
	//epollsever.Stop();
}

