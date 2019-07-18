/*
	创建1个客户端连接，创建1个发送线程
	线程循环发送登陆包
*/
#include "TcpSocket.h"
#include "BaseThread.h"
#include "Packet.h"
#include "VideoSeederPacke.h"
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include "ShmFIFO.h"
#include "Imageget.h"


class CSendThread;
//
CTcpSocket *client; //定义1个客户端连接
int sendPacknum = 0; //发包总数
CSendThread* tsend; //定义1个发送线程


//定义数据包发送线程
class CSendThread: public CBaseThread
{
public:
	CSendThread()
	{
		m_pack.Login();
        //client->Write(m_pack.getData(), m_pack.getSize());
		// m_pack.getSer_num(0x2001);
		 client->Write(m_pack.getData(), m_pack.getSize());
	};
	~CSendThread(){};
	virtual int run();
	void Sleep(int ms);
private:
    CShmFIFO m_sendFIFO;
	CPacket m_pack; //要发送的数据包
    CImageGet * m_ImgThread;
};

//毫秒级 延时
void CSendThread::Sleep(int ms)
{
	struct timeval delay;
	delay.tv_sec = 0;
	delay.tv_usec = ms * 1000; //20ms
	select(0, NULL, NULL, NULL, &delay);//函数用于监视的文件描述符的变化情况——读写或是异常。
}

int CSendThread::run()
{
	while(m_bRun)
	{
		//sleep(1);
		m_pack.Login();
		//m_pack.GetArea();
		
		sendPacknum++;
        client->Write(m_pack.getData(), m_pack.getSize());
        //client->Write(m_pack.getData(), m_pack.getSize());
		//client->Readn(m_pack.getData(), m_pack.getSize());
		// client->Readn((char *)m_pack.getHeader(),sizeof(packet_header_t));
  		//m_pack.setBodysize(m_pack.getHeader()->usrlenth);
  		//m_pack.setSize(sizeof(packet_header_t)+m_pack.getHeader()->usrlenth);
  		//client->Readn((char *)m_pack.getBody(),m_pack.getHeader()->usrlenth);
		m_pack.Getpacket(client);
        printf("%d\n",m_pack.getSize());
		if(((packet_tali_st*)m_pack.getTali())->pack_tail!=0x05)
    	{
        	m_pack.Getpacket(client);
    	}
		switch(m_pack.getHeader()->funcId)
        {
        case 0x0001:
        	{
            res_login_st * plogin =(res_login_st *) (m_pack.getBody());
            printf("client[x] receive:%d:%d\n",plogin->user_id,plogin->login_ret);
            client->setID(plogin->user_id);
            
             // Sleep(1000);
             // m_pack.Getrecord(plogin->user_id);
             // client->Write(m_pack.getData(), m_pack.getSize());
        	}
            break;
        case 0x1001:
        	{
        	VideoChannel * Channel =(VideoChannel *) (m_pack.getBody());
            printf("client[x] receive:%d:%d:%s\n",Channel->classes_count,Channel->classes_id,Channel->classes_name);
        	}
        	break;
        case 0x1003:
        	{
        	VideoArea * Area =(VideoArea *) (m_pack.getBody());
            printf("client[x] receive:%d:%d:%d:%s\n",Area->area_count,Area->classes_id,Area->area_id,Area->area_name);
        	}
        	break;
        case 0x1004:
        	{
        		VideoList *list=(VideoList *) (m_pack.getBody());
        		 printf("video_count:%d,VideoID:%d,ClassID:%d,AreaID:%d,Videoname:%s,playtimes:%d,Videonew:%c,VideoImg:%s,VideoAddr:%s\n",
        			list->video_count,list->video_id,list->classes_id,list->area_id,
        			list->video_name,list->play_times,list->is_new,list->video_image,list->video_address);
      
        	}
            break;
        case 0x1005:
            {
                PlayHistory_t * Area =(PlayHistory_t *) (m_pack.getBody());
                printf("client[x] receive:%d:%d\n",Area->video_id,Area->video_seek);
            }
            break;
        case 0x1011:
            {
                bool a=true;
                m_sendFIFO.init(ftok(".", 3),sizeof(Image_t),300);
                m_ImgThread=new CImageGet(m_sendFIFO);
                m_ImgThread->start();
                while(a)
                {
                Image_t *img=(Image_t *)(m_pack.getBody());
                if(strcmp(img->img_name,"")!=0 &&strcmp(img->img_name,"end")!=0)
                {
                    m_sendFIFO.write(img);
                    m_pack.Getpacket(client);
                }
                else if(strcmp(img->img_name,"end")==0)
                {
                    m_sendFIFO.write(img);
                    a=false;
                }
                else
                {
                    a=false;
                }
                }
            }
            break;
        case 0x2001:
            {
                char *strnum = NULL;
                if(m_pack.getHeader()->usrlenth == 23)
                {
                    strnum=(char *) (m_pack.getBody());
                    printf("%s\n", strnum);
                    m_pack.UploadVideoPlay(client->getID(), 220001, strnum);
                    client->Write(m_pack.getData(), m_pack.getSize());
                }
                else
                {
                    UpLoad *up=(UpLoad *) (m_pack.getBody());
                    printf("result:%i update_flowid:%s\n", up->results, up->update_flowid);
                }
            }
            break;
        case 0x2002:
            {
                char *strnum = NULL;
                if(m_pack.getHeader()->usrlenth == 23)
                {
                    strnum=(char *) (m_pack.getBody());
                    printf("%s\n", strnum);
                    m_pack.UploadVideoRecord(client->getID(), 220001, 90, strnum);
                    client->Write(m_pack.getData(), m_pack.getSize());
                }
                else
                {
                    UpLoad *up=(UpLoad *) (m_pack.getBody());
                    printf("result:%i update_flowid:%s\n", up->results, up->update_flowid);
                }
            }
            break;

        }
		Sleep(100);
	}
	
	return 0;
}

int main(int argc, char * argv[])
{
	 //Welcome
    printf("\n/*---------------欢迎来到聊天室---------------*/\n");

    printf("正在连接服务器..\n");

	CHostAddress addr("127.0.0.1", 8001);
	
	client = new CTcpSocket();
	client->Connect(addr);
	
	printf("连接服务器成功!\n");
	tsend = new CSendThread();
	tsend->start();
	
	 while(1)
	 {
	 	sleep(1);
	 	printf("sendPacknum=%d \n", sendPacknum);
	 }
	printf("客户端：退出!\n");
    printf("/*--------------------------------------------*/\n\n");
    return 0;
}

