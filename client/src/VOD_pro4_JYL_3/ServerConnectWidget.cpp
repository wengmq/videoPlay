#include "ServerConnectWidget.h"
#include <QDebug>
extern QTcpSocket *tcpClient;
extern QString RtspServerAddr;
ServerConnectWidget::ServerConnectWidget(QWidget *parent)
    : QWidget(parent)
{
    connectFlag = false;//���ӱ�־λ
    channelFlag = false;
    channelTotalCount=0;//Ƶ������
    channelCount = 0;//��ƵƵ������

    videoTotalCount=0;//��Ƶ����
    videoCount = 0;//��Ƶ����

    mainWidget = new MainWidget();
    UiInit();
    ConnectInit();

}

ServerConnectWidget::~ServerConnectWidget()
{

}

void ServerConnectWidget::UiInit()
{
    //��������
    this->setFixedSize(557,356);
    this->setWindowTitle("������");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CustomizeWindowHint);  //�Ѵ������ó�û��ܵ�
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2-20);
    backgroundLab = new QLabel(this);
    backgroundLab->setGeometry(0,0,577,356);
    backgroundLab->setStyleSheet("QLabel{border-image:url(../image/serverLogin.jpg);}");


    //�ؼ�����
    ipEdit = new QLineEdit("",this);
    ipEdit->setPlaceholderText("������IP��ַ");
    ipEdit->setGeometry(233,87,290,40);
    //ipEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");



    portEdit = new QLineEdit("",this);
    portEdit->setPlaceholderText("������˿ں�");
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

    //��ȡRTSP��ַ
    RtspServerAddr = ipEdit->text();

    //TCP ����
    tcpClient->connectToHost(ip,port);
    //�����жϷ���ֵ��ֵ��connectFlag
    connectFlag = tcpClient->waitForConnected(1000);

    if(connectFlag)
    {
        channel_pack.RequestChannel();//����Ƶ�������
        tcpClient->write(channel_pack.getData(),channel_pack.getSize()); //�����������ݰ�

        video_pack.RequestVideoList(1);
        tcpClient->write(video_pack.getData(),video_pack.getSize());//������Ƶ�������ݰ�

        qDebug("���������ӳɹ�");
        timeRead->start(200);
    }
    else
    {
        QMessageBox::information(NULL,"��ʾ","����������ʧ��");
        ipEdit->clear();
        portEdit->clear();
    }

}

void ServerConnectWidget::ChannelPacketReadSlot()
{
    //��ȡ��Ƶ���ݣ�������ҳ��ʾ��Ƶ��Ϣ
    //��ת��������
    if(!channelFlag)
    {
        tcpClient->read(pack_ret.getData(),pack_ret.getSize());
        pack_ret.unpack();


        if(pack_ret.getHeader()->funid==0x02)
        {
            qDebug()<<"Ƶ���հ�";
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
            qDebug()<<"�б��հ�";
            pData1 = *((video_list_t *)pack_ret.getBody());
//            qDebug()<<"222";
//            qDebug()<<"pData1.area_id��"<<pData1.area_id;
//            qDebug()<<"pData1.video_count"<<pData1.video_count;
//            qDebug("pData1.video_name��%s",pData1.video_name);

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
            qDebug("��ƵƵ���������������洢�����ݣ�%d,%s",i,channel_data.at(i).channel_name);
        }

        for(int i=0;i<videoCount;i++)
        {
            qDebug("��Ƶ�б������������洢�����ݣ�%d,%s",i,video_data.at(i).video_name);
        }

        //���ӷ�������ȡ����Ƶ�����ڽ�������ʾ
        //
        if((channelCount == channelTotalCount) && (videoCount == videoTotalCount) && videoCount>0 && channelCount>0)
        {
            channelFlag=true;
            qDebug("���ݳ�ʼ�����");

            mainWidget->contentWidget->contentWidgetTiTleBar->setChannleData(channel_data);
            mainWidget->contentWidget->contentBottomWidget->videoWidget->videoWidgetLower->setVideoData(video_data);
            mainWidget->show();
            this->hide();
            timeRead->stop();
        }
    }

}

