#include "QQSendThread.h"


CQQSendThread::CQQSendThread(CShmFIFO &fifo)
	:m_fifo(fifo)
{
       // m_fifo.open(KEY_FIFO_SEND, m_packet.getSize(), 100);
}

CQQSendThread::~CQQSendThread()
{
}

int CQQSendThread::run(void)
{
    printf("3333333\n");
	CTcpSocket client;
	
	//thread while(1)
        //m_bRun��ʼ��ʱΪfalse
       // while(!this->m_bRun)
        while(this->m_bRun)
	{
            //int a = 1;//((Login_ret_t *)m_packet.getBody())->ret
            printf("444444\n");
                //�ӹ����ڴ��ж�ȡ�����ݵ�m_packet
		m_fifo.read(m_packet.getData());

                //������Ϣ���͸��ͻ���
		m_packet.unpack();
               // printf("m_fifo m_packet.getHeader(): %d\n",m_packet.getHeader()->optid);
                client.SetSocket(m_packet.getHeader()->fd);
                printf("client.SetSocket(m_packet.getHeader()->fd): %d \n",m_packet.getHeader()->fd);
               // printf("body ret :%d",a);
                m_packet.pack();
		client.Writen(m_packet.getData(), m_packet.getSize());
	}

	return 0;
}

