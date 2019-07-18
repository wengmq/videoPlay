#include "ShmFIFO.h"
#include "Packet.h"
#include "BaseThread.h"
#include "PThreadPool.h" 
#include "PThreadCond.h" 
#include "VideoSeederPacke.h"
#include "CSDB.h"
#include "stdio.h"
/*使用epoll模式接收多客户端数据，并应答*/
/*****
1.读recvFIFO
2.解包
3.根据funid处理包，和数据库交互
4.重新生成返回包（带fd）,重新修改funid/optid/len/
5.写入sendFIFO
*/
class CQQTask: public CTask
{
public:
    CQQTask(CShmFIFO &send, CPacket *packet)
        :m_send(&send),m_packet(packet)
    {
        db=db->Getdata((char*)("data.db"));
    }

    CQQTask(){};

    int run()
    {
        //1.unpack
        //2.deal the packet by funid
        //3.open data

        //判断收到的包是否正常
        if(((packet_tali_st*)m_packet->getTali())->pack_tail!=0x05)
        {
            return 0;
        }

        switch(m_packet->getHeader()->funcId)
        {
        case 0x0001:
            m_packet->Login_call(db);
            break;
        case 0x1001:
            m_packet->Class_call(db,m_send);
            return 0;
            break;
        case 0x1003:
            m_packet->Area_call(db,m_send);
            return 0;
            break;
        case 0x1002:
            m_packet->Type_call(db,m_send);
            return 0;
            break;
        case 0x1004:
            m_packet->videoList_call(db,m_send);
            return 0;
            break;
        case 0x1005:
            m_packet->record_call(db,m_send);
            return 0;
            break;
        case 0x2001:
            if(m_packet->getHeader()->usrlenth == 0)
                m_packet->Ser_num(0x2001);
            else
            {
                m_mutex.lock();
                m_packet->UploadVideoPlay_call(db);
                m_mutex.unlock();
            }
            break;
        case 0x2002:
            if(m_packet->getHeader()->usrlenth == 0)
                m_packet->Ser_num(0x2002);
            else
            {
                m_mutex.lock();
                m_packet->UploadVideoRecord_call(db);
                m_mutex.unlock();
            }
            break;

        }
        //3.return packet
        m_send->write(m_packet->getData(),m_packet->getSize());//写入m_send
        return 0;
    }
private:
    CSDB *db;
    CPThreadMutex m_mutex;
    CShmFIFO *m_send;
    CPacket * m_packet;
};

class CBackServer
{
public:
    CBackServer()
    {
        m_pool = new CThreadPool(300, 30, 5);
        m_sendFIFO.open(KEY_FIFO_SEND, 248, 100);//m_packet.getSize()
        m_recvFIFO.open(KEY_FIFO_RECV, 248, 100);//m_packet.getSize()
        m_packet.setBodysize(10);
    }
    ~CBackServer(){};

    int run()
    {
        while(1)
        {
            //1.read from recvFIFO

            m_recvFIFO.read(m_packet);//m_packet.getData()
            //m_packet.pack();
            //2.create task
            CQQTask *t = new CQQTask(m_sendFIFO,&m_packet);//将recvFIFO的数据写入sendFIFO
            //3.add task to pool
            m_pool->addTask(t);
        }
        return 0;
    }

private:
    CPacket m_packet;
    CShmFIFO m_sendFIFO;
    CShmFIFO m_recvFIFO;

    CPThreadMutex m_mutex; //for client
    CThreadPool *m_pool;
};

int main(int argc, char * argv[])
{
    printf("\n/*-----------------后置服务器-----------------*/\n");

    //后置服务器
    printf("后置服务器：开启!\n");
    CBackServer back;

    back.run();

    //Exit
    printf("后置服务器：退出!\n");
    printf("/*--------------------------------------------*/\n\n");
    return 0;
}
