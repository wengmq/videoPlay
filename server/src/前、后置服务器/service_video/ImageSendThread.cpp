#include "ImageSendThread.h"

CImageSendThread::CImageSendThread(int &fd,CPacket& m_packet)
    :m_packet(m_packet)
{
    //m_fifo.open(KEY_FIFO_SEND, m_packet.getSize(), 100);
    this->fd=fd;
    db=db->Getdata((char*)("data.db"));
}
CImageSendThread::~CImageSendThread()
{
}
int CImageSendThread::run(void) 
{
    char **dbResult;
    int nRow=0, nColumn=0;
    int infd;
    int n;
    Image_t * img=new Image_t;
    CTcpSocket clinet(this->fd);
    db->Get_table((char *)"select VideoImg from VideoInfo ", &dbResult, &nRow,&nColumn);
    for (int j = 1; j <= nRow; ++j)
    {
        printf("VideoImg:%s\n",dbResult[j*(nColumn)]);
        infd = open(dbResult[j*(nColumn)],O_RDONLY);
        if(-1 == infd){
            perror("picpure open");
            exit(1);
        }
        while((n = read(infd,img->image,MAX_LEN)) > 0){
            strcpy(img->img_name,dbResult[j*(nColumn)]);
            m_packet.videoImg_res(img);
            //m_packet.pack();
            sleep(0.001);
            clinet.Writen(m_packet.getData(),m_packet.getSize());
        }
        close(infd);
    }
    strcpy(img->img_name,"end");
    strcpy(img->image,"");
    m_packet.videoImg_res(img);
    clinet.Writen(m_packet.getData(),m_packet.getSize());
    db->Free_table(dbResult);
    return 0;
}



