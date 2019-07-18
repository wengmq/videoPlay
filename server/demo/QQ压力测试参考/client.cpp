#include "commen.h"

#include "Socket.h"
#include "BaseThread.h"
#include "EpollTcpClient.h"


#define  CLIENTMAX   1000    //����ͻ�����������
#define  CLIENTNUM    100    //����һ��ͻ�����������

class CSendThread;
class CRecvThread;



/*------------------------------------------------------------*/
TCPClient* client[1000];  //����1000���ͻ�������
CSendThread* tsend[10];   //����10�������߳�
CRecvThread* trecv;   //����1�������߳�


int  connectnum=0;    //��������
int  sendPacknum=0;   //��������
int  recvPacknum=0;   //�հ�����
int  loginSuccessnum=0;   //��¼�ɹ�����
int  loginFailednum=0;    //��¼ʧ������


/*------------------------------------------------------------*/
Packet pack={{0},{0}};


/*�������ݰ������߳�*/
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
	Packet *m_pack;   //Ҫ���͵����ݰ�
	int m_number;   //�̱߳��

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

/*�������ݽ����߳�*/
class CRecvThread : public CBaseThread
{
public:
	CRecvThread(int num)
	{
	      m_tnum = num;	  
	};
	CRecvThread(){};
	int run();
	void stop(); //��дֹͣ�߳�
private:
	int  m_tnum;    //�����̱߳�ţ����ڿ��ƶ�Ӧ�Ŀͻ���fd
    CEpollTcpClient m_epoll;
};

/*
һ���߳̽���100���ͻ��˵����ݰ�,
����ʹ��epollģ�ͣ�ͬʱ������100������
*/
int CRecvThread::run()
{
    int i=0;

	// ���1000���ͻ�������������
    for(i=0;i<1000;i++)
    {
        m_epoll.AddEvent(client[i]->getfd(), EPOLLIN);
	}
	
	m_epoll.Start();  //����epollѭ��

    return 0;
}

void CRecvThread::stop()
{
    m_bRun = false;
    m_epoll.Stop();  //ֹͣepollѭ��
}

//----------------------------------------

/*�������ݴ�ӡ�߳�*/
class CPrintThread : public CBaseThread
{
public:
	CPrintThread(){};
	int run();
};

int CPrintThread::run()
{
	//�ͻ��˴�ӡͳ������
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
	
	//���߳̿�������
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


