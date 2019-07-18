#include "ServerConnectWidget.h"
#include <QDebug>
extern QTcpSocket *tcpClient;
extern QString RtspServerAddr;
ServerConnectWidget::ServerConnectWidget(QWidget *parent)
    : QWidget(parent)
{
    connectFlag = false;//连接标志位
    channelFlag = false;
    channelTotalCount=0;//频道总数
    channelCount = 0;//视频频道包数

    videoTotalCount=0;//视频总数
    videoCount = 0;//视频包数

    mainWidget = new MainWidget();
    UiInit();
    ConnectInit();

}

ServerConnectWidget::~ServerConnectWidget()
{

}

void ServerConnectWidget::UiInit()
{
    //窗口设置
    this->setFixedSize(557,356);
    this->setWindowTitle("爱奇艺");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CustomizeWindowHint);  //把窗口设置成没框架的
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2-20);
    backgroundLab = new QLabel(this);
    backgroundLab->setGeometry(0,0,577,356);
    backgroundLab->setStyleSheet("QLabel{border-image:url(../image/serverLogin.jpg);}");


    //控件设置
    ipEdit = new QLineEdit("",this);
    ipEdit->setPlaceholderText("请输入IP地址");
    ipEdit->setGeometry(233,87,290,40);
    //ipEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");



    portEdit = new QLineEdit("",this);
    portEdit->setPlaceholderText("请输入端口号");
    portEdit->setGeometry(233,147,290,40);
    //ipEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(521,0,36,36);
    closeBtn->setIcon(QIcon("../image/btn/title/close.jpg"));
    closeBtn->setIconSize(QSize(36,36));
    closeBtn->setFlat(true);
    closeBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");

    connectBtn = new QPushButton(this);
    connectBtn->setGeometry(233,230,290,40);
    connectBtn->setIcon(QIcon("../image/btn/login_btn2.jpg"));
    connectBtn->setIconSize(QSize(290,40));
    connectBtn->setFlat(true);
    connectBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
}



void ServerConnectWidget::ConnectInit()
{
    timeRead = new QTimer();
    connect(connectBtn,SIGNAL(released()),this,SLOT(ConnectSlot()));
    connect(timeRead,SIGNAL(timeout()),this,SLOT(ChannelPacketReadSlot()));
    connect(closeBtn,SIGNAL(released()),this,SLOT(close()));
}

void ServerConnectWidget::ConnectSlot()
{
    QString ip;
    int port;

    ip=ipEdit->text();
    port= portEdit->text().toInt();

    //获取RTSP地址
    RtspServerAddr = ipEdit->text();

    //TCP 连接
    tcpClient->connectToHost(ip,port);
    //连接判断返回值赋值给connectFlag
    connectFlag = tcpClient->waitForConnected(1000);

    if(connectFlag)
    {
        channel_pack.RequestChannel();//设置频道请求包
        tcpClient->write(channel_pack.getData(),channel_pack.getSize()); //发送请求数据包

        video_pack.RequestVideoList(1);
        tcpClient->write(video_pack.getData(),video_pack.getSize());//发送视频请求数据包

        qDebug("服务器连接成功");
        timeRead->start(200);
    }
    else
    {
        QMessageBox::information(NULL,"提示","服务器连接失败");
        ipEdit->clear();
        portEdit->clear();
    }

}

void ServerConnectWidget::ChannelPacketReadSlot()
{
    //获取视频数据，用于主页显示视频信息
    //跳转到主界面
    if(!channelFlag)
    {
        tcpClient->read(pack_ret.getData(),pack_ret.getSize());
        pack_ret.unpack();


        if(pack_ret.getHeader()->funid==0x02)
        {
            qDebug()<<"频道收包";
            pData = *((reply_channel_t *)pack_ret.getBody());
            channel_data.append(pData);

            channelCount++;
            if(channelCount==1)
            {
                channelTotalCount= pData.channel_count;
            }
            qDebug("%s",pData.channel_name);
        }



        if(pack_ret.getHeader()->funid==0x03)
        {
            qDebug()<<"列表收包";
            pData1 = *((video_list_t *)pack_ret.getBody());
//            qDebug()<<"222";
//            qDebug()<<"pData1.area_id："<<pData1.area_id;
//            qDebug()<<"pData1.video_count"<<pData1.video_count;
//            qDebug("pData1.video_name：%s",pData1.video_name);

            video_data.append(pData1);
            qDebug()<<"333";
            videoCount++;
            if(videoCount==1)
            {
                videoTotalCount= pData1.video_count;
                qDebug("%d",pData1.video_count);
            }
        }

        for(int i=0;i<channelCount;i++)
        {
            qDebug("视频频道——————存储后数据：%d,%s",i,channel_data.at(i).channel_name);
        }

        for(int i=0;i<videoCount;i++)
        {
            qDebug("视频列表——————存储后数据：%d,%s",i,video_data.at(i).video_name);
        }

        //将从服务器获取是视频数据在界面上显示
        //
        if((channelCount == channelTotalCount) && (videoCount == videoTotalCount) && videoCount>0 && channelCount>0)
        {
            channelFlag=true;
            qDebug("数据初始化完成");

            mainWidget->contentWidget->contentWidgetTiTleBar->setChannleData(channel_data);
            mainWidget->contentWidget->contentBottomWidget->videoWidget->videoWidgetLower->setVideoData(video_data);
            mainWidget->show();
            this->hide();
            timeRead->stop();
        }
    }

}

