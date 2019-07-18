/*
    client1.c
    创建一个客户端连接，创建一个发送线程，
    线程中循环发送登录包
*/

#include "TcpSocket.h"
#include "PThreadBase.h"
#include "QQPacket.h"

class CSendThread;
//---------------------------------------------
CTcpSocket* client;  //定义1个客户端连接
int  sendPacknum=0;   //发包总数
CSendThread* tsend;   //定义1个发送线程

//---------------------------------------------

/*定义数据包发送线程*/
class CSendThread : public CThreadBase
{
public:
	CSendThread()
	{
		  m_pack.Login();
	};
	~CSendThread(){};
	virtual int run();
	void Sleep(int ms);
	
private:
	CQQPacket m_pack;   //要发送的数据包
};

/* 毫秒级 延时 */
void CSendThread::Sleep(int ms)
{	
	struct timeval delay;	
	delay.tv_sec = 0;	
	delay.tv_usec = ms * 1000; // 20 ms	
	select(0, NULL, NULL, NULL, &delay);
}


int CSendThread::run()
{
    while(m_bRun)
    {
		//sleep(1); //延时1s	
        client->Write(m_pack.getData(), m_pack.getSize());
		sendPacknum++;
		Sleep(10);
	}
	
	return 0;
}

//----------------------------------------
int main()
{
	CHostAddress addr("127.0.0.1", 8001);
	
    client = new CTcpSocket();
    client->Connect(addr);
    
    tsend = new CSendThread(); 
	tsend->start();

	while(1)
	{
	    sleep(3);	
		printf("sendPacknum=%d \n",sendPacknum);
	}
}


