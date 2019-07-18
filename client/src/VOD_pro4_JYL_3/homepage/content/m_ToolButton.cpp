#include "m_ToolButton.h"
#include <QDebug>
extern QString RtspServerAddr;
m_ToolButton::m_ToolButton(QWidget *parent)
    :QToolButton(parent)
{
    connect(this,SIGNAL(released()),this,SLOT(videoPlaySlot()));
}


void m_ToolButton::setVideoTypeMsg(int video_count,int video_id,int channel_id,const int type_ids[])
{
    this->video_count=video_count;
    this->video_id=video_id;
    this->channel_id=channel_id;
    for(int i=0;i<10;i++)
    {
        this->type_ids[i]=type_ids[i];
    }

}
void m_ToolButton::setVideoMsg(const char video_name[],int play_times,const char is_new,const char video_image[],const char video_address[])
{
    strcpy(this->video_name,video_name);
    this->play_times = play_times;
    strcpy(this->video_image,video_image);
    this->is_new = is_new;
    strcpy(this->video_address,video_address);
}


void m_ToolButton::videoPlaySlot()
{
    qDebug("视频id：%d",this->video_id);
    qDebug("视频地址：%s",this->video_address);
    qDebug()<<"ip地址："<<RtspServerAddr;
    FFVideoPlayer *new_p = new FFVideoPlayer();
    //设置视频源地址
    QString address= QString::fromUtf8(this->video_address); //本工程目录视频  本地播放

    QString url = QString("rtsp://")+ RtspServerAddr + QString("/")+ address;
    //rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov // 网络视频播放
    qDebug() << "home url = " << url;
    new_p->on_open_Btn_released(url);
    new_p->show();
}
