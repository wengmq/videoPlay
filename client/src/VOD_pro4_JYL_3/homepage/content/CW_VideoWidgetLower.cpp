#include "CW_VideoWidgetLower.h"
#include <QDebug>

int buttonFlag=0;


CW_VideoWidgetLower::CW_VideoWidgetLower(QWidget *parent): QFrame(parent)
{
    setMouseTracking(true);
    //UiInit();
}






void CW_VideoWidgetLower::UiInit()
{
   // btnVector = QVector<VideoToolButton *> (6);


    setStyleSheet(::main_style3);

    setMinimumSize(1000,160);
    setMaximumSize(1920,160);

    videoLagout = new QHBoxLayout(this);



    int videoCount = video_data_list.count();
    qDebug()<<videoCount;

    if(videoCount>0)
    {
        if(videoCount>6)
        {
            videoCount=6;
        }
        for(int i=0;i<videoCount;i++)
        {
            m_ToolButton *videoBtn = new m_ToolButton;
            videoBtn->setArrowType(Qt::NoArrow);
            videoBtn->setFixedSize(145,120);
            videoBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            videoBtn->setStyleSheet("QToolButton{border: none; background: rgb(245, 245, 245); color: rgb(0, 0, 0);}");
            videoBtn->setIconSize(QSize(145, 80));

            videoBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            videoBtn->setVideoTypeMsg(video_data_list.at(i).video_count,video_data_list.at(i).video_id,video_data_list.at(i).channel_id,video_data_list.at(i).type_ids);
            videoBtn->setVideoMsg(video_data_list.at(i).video_name,video_data_list.at(i).play_times,video_data_list.at(i).is_new,video_data_list.at(i).video_image,video_data_list.at(i).video_address);


            qDebug("video name %s",video_data_list.at(i).video_name);

            QAction *pAction = new QAction(this);
            pAction->setIcon(QIcon("../image/logo.jpg"));
            pAction->setText(QString::fromUtf8(video_data_list.at(i).video_name));
            videoBtn->setDefaultAction(pAction);

            video_btn_list.append(videoBtn);
            buttonFlag=i;
            //connect(video_btn_list.at(i),SIGNAL(released()),this,SLOT(videoPlaySlot()));
            //connect(this,SIGNAL(videoPlaySignal(const char[])),this,SLOT(videoPlaySlot(const char[])));
        }

    }
    else
    {
        qDebug("======无视频推荐=====");
    }

    if(video_btn_list.count()>0)
    {
        for(int i=0;i<video_btn_list.count();i++)
        {
            qDebug("======添加到布局管理器=====");
            videoLagout->addWidget(video_btn_list.at(i));
        }
    }
}



void CW_VideoWidgetLower::setVideoData(QList<video_list_t > dataList)
{
    video_data_list = dataList;
    UiInit();
}


void CW_VideoWidgetLower::videoPlaySlot()
{
//    FFVideoPlayer *new_p = new FFVideoPlayer();
//    //设置视频源地址
//    QString url="../dadi.mp4"; //本工程目录视频  本地播放
//    //
//    //rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov // 网络视频播放
//    qDebug() << "home url = " << url;

//    new_p->on_open_Btn_released(url);
//    new_p->show();

    qDebug("视频%d ：%d",buttonFlag,video_btn_list.at(buttonFlag)->video_id);
}

void CW_VideoWidgetLower::videoPlaySignalEmitSlot()
{
    emit videoPlaySignal(video_btn_list.at(buttonFlag)->video_name);
}
