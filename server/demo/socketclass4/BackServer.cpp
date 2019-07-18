
#include "PThreadPool.h"
#include "PThreadBase.h"
#include "PThreadCond.h"
#include "ShmFIFO.h"
#include "QQPacket.h"

/*ʹ��epollģ�ͽ��ն�ͻ������ݣ���Ӧ��*/
/*****
1. ��recvFIFO
2. ���
3. ���ݰ�funid������������ݿ⽻��
4. �������ɷ��ذ�(��fd) �������޸�funid/optid/len/
5. д��sendFIFO
*/
class CQQTask: public CTask
{
public:
	CQQTask(CShmFIFO &send, CQQPacket& packet)
		:m_send(&send), m_packet(packet)
	{
	}
	
	CQQTask(){};

	int run()
	{
		
		//1. unpack
		m_packet.unpack();
		
		//2. deal the packet by funid
		void *pData = m_packet.getBody();
		switch(m_packet.getHeader()->funid)
		{
		case 0x1:
			Login_t *plogin = (Login_t*) (pData);
        	printf("Back recv:%s:%s\n", plogin->usr, plogin->psw);

			//return action
			break;
		}
		//3. return packet
		m_packet.pack(); 
		m_send->write(m_packet.getData());

		return 0;
	}

private:
	CShmFIFO *m_send;
	CQQPacket m_packet;
};


class CBackServer
{
public:
	CBackServer()
	{
		m_pool = new CThreadPool(20, 5, 5);
		m_sendFIFO.open(KEY_FIFO_SEND, m_packet.getSize(), 100);
		m_recvFIFO.open(KEY_FIFO_RECV, m_packet.getSize(), 100);
	}
	~CBackServer(){}

	int run()
	{
		while(1)
		{
			//1. read from recvFIFO
			m_recvFIFO.read(m_packet.getData());

			//2. create task
			CQQTask *t = new CQQTask(m_sendFIFO, m_packet);

			//3. add task to pool
			m_pool->addTask(t);
		}

		return 0;
	}
	
private:
	CQQPacket m_packet;
    CShmFIFO  m_sendFIFO;
    CShmFIFO  m_recvFIFO;
    
    CPThreadMutex m_mutex; // for client
    CThreadPool *m_pool;
};

int main()
{
	CBackServer back;

	back.run();
}

