#include "MainWidget.h"
#include "QDebug"
MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    loginFlag = false;
    loginWidget = new LoginWidget();
    UiInit();
    ConnectInit();
}


void MainWidget::UiInit()
{
    //��������
    this->setFixedSize(1000,588);
    this->setWindowTitle("������");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CustomizeWindowHint);  //�Ѵ������ó�û��ܵ�
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2-20);
    backgoundLab = new QLabel(this);
    backgoundLab->setGeometry(0,0,1000,588);
    backgoundLab->setStyleSheet("QLabel{border-image:url(../image/youngbackground.jpg);}");


    titleBar = new TitleBar(this);
    connect(titleBar->loginBtn,SIGNAL(released()),this,SLOT(UserLoginSlot()));
    connect(titleBar->minimumBtn,SIGNAL(released()),this,SLOT(showMinimized()));
    connect(titleBar->closeBtn,SIGNAL(released()),this,SLOT(close()));

    contentWidget = new ContentWidget(this);
    connect(contentWidget->contentBottomWidget->contentBottomWidgetTitleBar->recommendBtn,SIGNAL(released()),this,SLOT(VideoWidgetShowSlot()));
    connect(contentWidget->contentBottomWidget->contentBottomWidgetTitleBar->libBtn,SIGNAL(released()),this,SLOT(VideoLibWidgetShowSlot()));
//    connect(contentWidget->contentBottomWidget->videoWidget->videoWidgetLower->videoBtn1,\
//            SIGNAL(released()),this,SLOT(VideoPlaySlot()));

}


void MainWidget::ConnectInit()
{
//    connect(VedioButton1,SIGNAL(released()),this,SLOT(videPlay_solt()));
    connect(loginWidget,SIGNAL(LoginSuccessSignal(bool)),this,SLOT(LoginSuccessSLot(bool)));

}

void MainWidget::VidePlaySlot()
{
   // play->show();
   // this->hide();
    //play->StartPlay();
}

void MainWidget::UserLoginSlot()
{
   // play->show();
   // this->hide();
    //play->StartPlay();
    loginWidget->show();
}

void MainWidget::LoginSuccessSLot(bool loginFlag)
{
    this->loginFlag = loginFlag;
    if(this->loginFlag)
    {
        titleBar->loginBtn->setText("��¼�ɹ�");
        //���û����ż�¼��ʼ����������
        qDebug("������������������¼�ɹ�����������������");

    }
}

void MainWidget::VideoWidgetShowSlot()
{
    contentWidget->contentBottomWidget->videoWidget->show();
    contentWidget->contentBottomWidget->videoLibWidget->hide();
}

void MainWidget::VideoLibWidgetShowSlot()
{
    contentWidget->contentBottomWidget->videoLibWidget->show();
    contentWidget->contentBottomWidget->videoWidget->hide();
}

void MainWidget::VideoPlaySlot()
{
    FFVideoPlayer *new_p = new FFVideoPlayer();
    //������ƵԴ��ַ
    QString url="../dadi.mp4"; //������Ŀ¼��Ƶ  ���ز���
    //
    //rtsp://184.72.239.149/vod/mp4://BigBuckBunny_175k.mov // ������Ƶ����
    qDebug() << "home url = " << url;

    new_p->on_open_Btn_released(url);
    new_p->show();
}
