
#include "PThreadPool.h"
#include "PThreadBase.h"
#include "PThreadCond.h"
#include "ShmFIFO.h"
#include "QQPacket.h"
#include "CSinDB.h"
#include"BackServerFunction.h"
#include"CQQTask.h"
/*ʹ��epollģ�ͽ��ն�ͻ������ݣ���Ӧ��*/
/*****
1. ��recvFIFO
2. ���
3. ���ݰ�funid������������ݿ⽻��
4. �������ɷ��ذ�(��fd) �������޸�funid/optid/len/
5. д��sendFIFO
*/




class CBackServer
{
public:
	CBackServer()
	{
		m_pool = new CThreadPool(20, 5, 5);
		m_sendFIFO.open(KEY_FIFO_SEND, m_packet.getSize(), 100);
		m_recvFIFO.open(KEY_FIFO_RECV, m_packet.getSize(), 100);

                //�������ļ�
                CSinDB::GetSinDB();
	}
	~CBackServer(){}

	int run()
	{
		while(1)
		{
                        m_packet.dataClean();
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

