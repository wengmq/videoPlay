
#include "QQEpollTcpServer.h"


/*ʹ��epollģ�ͽ��ն�ͻ������ݣ���Ӧ��*/
int main()
{
	CHostAddress addr(NULL, 10086);
	CQQEpollTcpServer epollsever(addr);
	epollsever.Start();
	//epollsever.Stop();
}

