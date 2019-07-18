/*
    client1.c
    ����һ���ͻ������ӣ�����һ�������̣߳�
    �߳���ѭ�����͵�¼��
*/

#include "TcpSocket.h"
#include "PThreadBase.h"
#include "QQPacket.h"

class CSendThread;
//---------------------------------------------
CTcpSocket* client;  //����1���ͻ�������
int  sendPacknum=0;   //��������
CSendThread* tsend;   //����1�������߳�

//---------------------------------------------

/*�������ݰ������߳�*/
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
	CQQPacket m_pack;   //Ҫ���͵����ݰ�
};

/* ���뼶 ��ʱ */
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
		//sleep(1); //��ʱ1s	
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


