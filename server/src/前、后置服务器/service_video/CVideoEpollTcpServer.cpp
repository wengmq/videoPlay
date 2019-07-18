#include "CVideoEpollTcpServer.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include "TcpSocket.h"
#include <sys/resource.h>
#include "heartbeat.h"
Realtimelog_t reallog;

CVideoEpollTcpServer::CVideoEpollTcpServer(CHostAddress addr,unsigned int maxEvent,int timeout)
    :CEpollTcpServer(addr,maxEvent,timeout)
{
    hstop=true;
    struct rlimit rlim_new;
    m_packet=new CPacket;
    // m_sendFIFO.init(ftok(".", 1),m_packet->getSize(),100);
    // m_recvFIFO.init(ftok(".", 2),m_packet->getSize(),100);

    m_sendFIFO.init(KEY_FIFO_SEND,248,100);//m_packet->getSize()
    m_recvFIFO.init(KEY_FIFO_RECV,248,100);//m_packet->getSize()


    reallog.Eff_conn_num=0;//有效连接数
    reallog.Rec_pack_num=0;//接包数
    reallog.Con_pack_num=0;//发包数
    reallog.User_login_service_num=0;//用户登录业务数
    reallog.Gets_videolist_num=0;//获取视频列表数
    reallog.Gets_videorecord_num=0;//获取视频播放记录数
    reallog.UpLoad_videorecord_num=0;//上传视频播放记录数
    reallog.UpLoad_videoTime_num=0;//上传视频播放时间记录数

    //创建收发的线程，用于接收后置服务的包
    //在返回给QQ客户端
    Log=new CwriteLog();
    m_sendThread = new CVideoSezndThread(m_sendFIFO,Log);
    m_RealThread = new CRealtimelogs();
    
    if (setrlimit(RLIMIT_NOFILE , &rlim_new)!=0)
    {
        rlim_new.rlim_cur = rlim_new.rlim_max = 65535;
        printf("%d\n", (int)rlim_new.rlim_max);
        (void) setrlimit(RLIMIT_NOFILE , &rlim_new);
    }
}
CVideoEpollTcpServer::~CVideoEpollTcpServer()
{
    m_mclients.clear(); //删除信息表
    m_sendFIFO.destroy();
    m_recvFIFO.destroy();
    delete m_packet;
}

void CVideoEpollTcpServer::Start()
{
    this->m_bStop=false;
    //服务器启动后创建socket回送线程
    m_sendThread->start();
    m_RealThread->start();
    //Cheartbeat * p=new Cheartbeat(this);
    //p->start();
    while(!this->m_bStop)
    {
        int nevent=this->Wait();//等待epoll事件的发生
        if(nevent)
        {
            this->Run(nevent);//处理所发生的所有事件
        }
        else if(nevent==0)
        {
            OnTimeMonit(m_timeout,30);
        }
        //OnTimeMonit(m_timeout,120);//30 second timeout
    }
}
void CVideoEpollTcpServer::setTimeMonit(int MaxTime)
{
    OnTimeMonit(m_timeout,MaxTime);
}
void CVideoEpollTcpServer::Run(int nevent)
{
    for(int i = 0;i<nevent;i++)
    {
        //如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
        if((m_retEvent+i)->data.fd == m_tcpServer.GetSocket())
        {
            OnNewConnection();
            reallog.Eff_conn_num++;
        }
        //如果是已经连接的用户，并且收到数据，那么进行读入
        else if((m_retEvent+i)->events & EPOLLIN)
        {
            OnReadData((m_retEvent+i)->data.fd);
        }
    }
}

void CVideoEpollTcpServer::OnNewConnection()
{
    CTcpSocket client = m_tcpServer.Accept();
    AddEvent(client.GetSocket(),EPOLLIN);//EPOLLIN表示对应的文件描述符可以读（包括对端SOCKET正常关闭）

    QQCLIENT_T newclient;
    newclient.fd=client.GetSocket();
    newclient.delay=10;
    newclient.addr=client.GetRemoteAddr();
    //printf("FD:%d\n", client.GetSocket());
    m_mclients.insert(make_pair(client.GetSocket(),newclient));//Add to map
    lsc.push_back(client.GetSocket());
}

void CVideoEpollTcpServer::OnClientClose(int fd)
{
    DelEvent(fd,EPOLLIN);
    close(fd);
    //delete from map
    MP_CLIENT::iterator it;
    it = m_mclients.find(fd);
    if(it != m_mclients.end())
    {
        m_mutex.lock();
        m_mclients.erase(it); //remove from map
        LISTcli::iterator pant_it = lsc.begin();
        for (; pant_it != lsc.end(); pant_it++)
        {
            if (* pant_it ==fd)
            {
                lsc.erase(pant_it);
                break;
            }
        }
        reallog.Eff_conn_num--;
        m_mutex.unlock();
    }
}

void CVideoEpollTcpServer::OnReadData(int fd)
{
    CTcpSocket client(fd);
    int readBytes=m_packet->Getpacket(&client);
    if(readBytes==-1)
    {
        printf("client[%d] connect closed\n",fd);
        OnClientClose(fd);
    }
    else if((unsigned)readBytes != m_packet->getSize())
    {
        printf("client[%d] receive closed\n",fd);
        OnClientClose(fd);
    }
    else if(((packet_tali_st*)m_packet->getTali())->pack_tail!=0x05)
    {
        return ;
    }
    else
    {
        OnResetTime(fd);
        // m_packet->unpack();
        m_packet->getHeader()->fd=fd;//更新客户端fd
        switch(m_packet->getHeader()->funcId)
        {
        case 0x0000:
        {
            printf("fd:%d\n",fd);
            return ;
        }
            break;
        case 0x0001:
        {
            //Login_t * plogin =(Login_t *) (m_packet->getBody());
            //printf("client[%d] receive:%s:%s\n",fd,plogin->username,plogin->psw);//plogin->psw
            reallog.User_login_service_num++;
        }
            break;
        case 0x1004:
        {
            reallog.Gets_videolist_num++;
        }
            break;
        case 0x1005:
        {
            reallog.Gets_videorecord_num++;
        }
            break;
        case 0x2001:
        {
            if (m_packet->getHeader()->usrlenth > 0)
            {
                reallog.UpLoad_videorecord_num++;
            }
        }
            break;
        case 0x2002:
        {
            if (m_packet->getHeader()->usrlenth > 0)
            {
                reallog.UpLoad_videoTime_num++;
            }
        }
            break;
        case 0x1011:
        {
            m_ImgThread  =new CImageSendThread(fd,*m_packet);
            m_ImgThread->start();
            return ;
        }
            break;
        }

        m_packet->pack();           //重新打包
        m_recvFIFO.write(m_packet->getData(),m_packet->getSize());
        reallog.Rec_pack_num++;
        if(m_packet->getHeader()->usrlenth!=0)
            Log->writes((char *)m_packet->getBody(),m_packet->getHeader()->usrlenth,id[fd],m_packet->getHeader()->funcId,1);
        else
            Log->writes(NULL,0,id[fd],m_packet->getHeader()->funcId,1);
    }
    
}

void CVideoEpollTcpServer::OnTimeMonit(int Sec, int MaxTime)//超时处理
{
    MP_CLIENT::iterator its;
    LISTcli::iterator itp;
    LISTcli::iterator it=lsc.begin();
    for(;it!=lsc.end();)
    {
        if(hstop)
        {
            its = m_mclients.find(*it);
            if(its->second.delay+Sec >= MaxTime)
            {
                itp=++it;
                printf("delete client:[%d]\n", *(--it));
                OnClientClose(*(it));//删除信息
                it=itp;
                if (it==lsc.end())
                {
                    return ;
                }
            }
            else
            {
                m_mutex.lock();
                its->second.delay +=Sec;
                m_mutex.unlock();
                it++;
            }
        }
    }
}

bool CVideoEpollTcpServer::OnResetTime(int fd)//时间复位
{
    MP_CLIENT::iterator it=m_mclients.begin();
    it=m_mclients.find(fd);
    if(it !=m_mclients.end())
    {
        m_mutex.lock();
        it->second.delay=0;
        m_mutex.unlock();
        return true;
    }
    return false;
}


