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
	CTcpSocket client;
	

        while(this->m_bRun)
	{


                //从共享内存中读取包数据到m_packet
		m_fifo.read(m_packet.getData());

                //将包信息发送给客户端
		m_packet.unpack();

                client.SetSocket(m_packet.getHeader()->fd);
                printf("QQSendThread(m_packet.getHeader()->fd): %d \n",m_packet.getHeader()->fd);

                m_packet.pack();
		client.Writen(m_packet.getData(), m_packet.getSize());
	}

	return 0;
}

