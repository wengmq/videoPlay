#include "commen.h"

#include "Socket.h"
#include "BaseThread.h"
#include "EpollTcpClient.h"


#define  CLIENTMAX   1000    //定义客户端连接数量
#define  CLIENTNUM    100    //定义一组客户端连接数量

class CSendThread;
class CRecvThread;



/*------------------------------------------------------------*/
TCPClient* client[1000];  //定义1000个客户端连接
CSendThread* tsend[10];   //定义10个发送线程
CRecvThread* trecv;   //定义1个接收线程


int  connectnum=0;    //连接总数
int  sendPacknum=0;   //发包总数
int  recvPacknum=0;   //收包总数
int  loginSuccessnum=0;   //登录成功总数
int  loginFailednum=0;    //登录失败总数


/*------------------------------------------------------------*/
Packet pack={{0},{0}};


/*定义数据包发送线程*/
class CSendThread : public CBaseThread
{
public:
	CSendThread(int number, Packet *pack)
	{
		  m_pack = pack;
		  m_number = number;
	};
	CSendThread(){};
	int run();
private:
	Packet *m_pack;   //要发送的数据包
	int m_number;   //线程编号

};

int CSendThread::run()
{
    int i=0;
    while(m_bRun)
    {
        sleep(1);
        for(i=m_number*100;i<m_number*100+100;i++)
		{
		    client[i]->send(m_pack);
			sendPacknum++;
    	}		
	}
	
	return 0;
}

//----------------------------------------

/*定义数据接收线程*/
class CRecvThread : public CBaseThread
{
public:
	CRecvThread(int num)
	{
	      m_tnum = num;	  
	};
	CRecvThread(){};
	int run();
	void stop(); //重写停止线程
private:
	int  m_tnum;    //发送线程编号，用于控制对应的客户端fd
    CEpollTcpClient m_epoll;
};

/*
一个线程接收100个客户端的数据包,
必须使用epoll模型，同时监视这100个连接
*/
int CRecvThread::run()
{
    int i=0;

	// 添加1000个客户端连接描述符
    for(i=0;i<1000;i++)
    {
        m_epoll.AddEvent(client[i]->getfd(), EPOLLIN);
	}
	
	m_epoll.Start();  //启动epoll循环

    return 0;
}

void CRecvThread::stop()
{
    m_bRun = false;
    m_epoll.Stop();  //停止epoll循环
}

//----------------------------------------

/*定义数据打印线程*/
class CPrintThread : public CBaseThread
{
public:
	CPrintThread(){};
	int run();
};

int CPrintThread::run()
{
	//客户端打印统计数据
	while(m_bRun)
	{		
		sleep(3);	
		printf("sendPacknum=%d, recvPacknum=%d\n",sendPacknum,recvPacknum);
	}

    return 0;
}

//----------------------------------------
#include <termios.h>
int getch(void) 
{ 
    struct termios tm, tm_old; 
    int fd = STDIN_FILENO, c; 

    if(tcgetattr(fd, &tm) < 0) 
            return -1; 

    tm_old = tm; 

    tm.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	
    if(tcsetattr(fd, TCSANOW, &tm) < 0) 
            return -1; 

    c = fgetc(stdin); 

    if(tcsetattr(fd, TCSANOW, &tm_old) < 0) 
            return -1; 

    return c; 
} 



int main()
{
	int i=0;
	Packet packet1={{0},{0}};
	strcpy(packet1.body,"admin:123456");	//success
	Packet packet2={{0},{0}};
	strcpy(packet2.body,"admin:000000");	//failed

    for(i=0;i<1000;i++)
    {
        client[i]= new TCPClient(8001, "127.0.0.1");
    }

    for(i=0;i<10;i+=2)
    {
        tsend[i] = new CSendThread(i,&packet1); 
	    //tsend[i]->start();
		tsend[i+1] = new CSendThread(i+1,&packet2);
		//tsend[i+1]->start();
    }

	trecv = new CRecvThread(0);
	//trecv->start();

	CPrintThread tprint;
	//tprint.start();
	
	//主线程控制流程
	while(1)
	{
	    char ch=getch();
		printf("ch=%d ",ch);
	    if( ch == 10 || ch==13)
	    {
	        printf("start...\n");
	        for(i=0;i<10;i++)
		    {
			    tsend[i]->start();				
		    }

			trecv->start();
			tprint.start();
		}
		else
		{		
		    printf("stop...\n");
			for(i=0;i<10;i++)
			    tsend[i]->stop();

			sleep(2);
			trecv->stop();
			sleep(1);
			tprint.stop();
		}
	}

}


