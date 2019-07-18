
#include "PThreadPool.h"
#include "PThreadBase.h"
#include "PThreadCond.h"
#include "ShmFIFO.h"
#include "QQPacket.h"
#include "CSinDB.h"
#include"BackServerFunction.h"
#include"CQQTask.h"
/*使用epoll模型接收多客户端数据，并应答*/
/*****
1. 读recvFIFO
2. 解包
3. 根据包funid处理包，和数据库交互
4. 重新生成返回包(带fd) ，重新修改funid/optid/len/
5. 写入sendFIFO
*/




class CBackServer
{
public:
	CBackServer()
	{
		m_pool = new CThreadPool(20, 5, 5);
		m_sendFIFO.open(KEY_FIFO_SEND, m_packet.getSize(), 100);
		m_recvFIFO.open(KEY_FIFO_RECV, m_packet.getSize(), 100);

                //打开数据文件
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

