#include "CVideoSendThread.h"
#include "CVideoEpollTcpServer.h"

int id[70000];
CVideoSendThread::CVideoSendThread(CShmFIFO &fifo,CwriteLog * Lwr)
    :m_fifo(fifo)
{
    Log=Lwr;
    //m_fifo.open(KEY_FIFO_SEND, m_packet.getSize(), 100);
}
CVideoSendThread::~CVideoSendThread()
{
}
int CVideoSendThread::run(void) 
{
    CTcpSocket clinet;
    //thread while(1)
    while(this->m_bRun)
    {
        
        //从共享内存中读取数据，如果里面有后置服务器写入的数据 ，则将数据读到m_packet
        m_fifo.read(m_packet);

        if (m_packet.getHeader()->funcId==0x0001)
        {
            res_login_st * plogin =(res_login_st *) (m_packet.getBody());
            id[m_packet.getHeader()->fd]=plogin->user_id;
        }
        //发送应答包给客户端
        m_packet.pack();
        clinet.SetSocket(m_packet.getHeader()->fd);
        clinet.Writen(m_packet.getData(),m_packet.getSize());
        reallog.Con_pack_num++;//发包数+1

        //将发送的应答包数据写入日志文件
        if(m_packet.getHeader()->usrlenth!=0)
            Log->writes((char *)m_packet.getBody(),m_packet.getHeader()->usrlenth,id[m_packet.getHeader()->fd],m_packet.getHeader()->funcId,0);
        else
            Log->writes(NULL,0,id[m_packet.getHeader()->fd],m_packet.getHeader()->funcId,0);
    }
    return 0;
}
