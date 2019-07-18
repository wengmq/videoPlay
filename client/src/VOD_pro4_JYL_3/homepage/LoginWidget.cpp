#include "LoginWidget.h"
extern QTcpSocket *tcpClient;
//extern QTimer *timerRead;

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
{
    loginFlag = false;
    UiInit();
    ConnectInit();

}

LoginWidget::~LoginWidget()
{

}

void LoginWidget::UiInit()
{
    //窗口设置
    this->setFixedSize(557,356);
    this->setWindowTitle("爱奇艺");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::CustomizeWindowHint);  //把窗口设置成没框架的
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2-20);

    backgoundLab = new QLabel(this);
    backgoundLab->setGeometry(0,0,577,356);
    backgoundLab->setStyleSheet("QLabel{border-image:url(../image/login.jpg);}");


    //控件设置
    usernameEdit = new QLineEdit("",this);
    usernameEdit->setPlaceholderText("请输入账号");
    usernameEdit->setGeometry(233,87,290,40);
    //usernameEdit->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    passwordEdit = new QLineEdit("",this);
    passwordEdit->setPlaceholderText("请输入密码");
    passwordEdit->setGeometry(233,147,290,40);
    //edit_Password->setStyleSheet("background:transparent;border-width:0;border-style:outset");


    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(521,0,36,36);
    closeBtn->setIcon(QIcon("../image/btn/title/close.jpg"));
    closeBtn->setIconSize(QSize(36,36));
    closeBtn->setFlat(true);
    closeBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");

    loginBtn = new QPushButton(this);
    loginBtn->setGeometry(233,230,290,40);
    loginBtn->setIcon(QIcon("../image/btn/login_btn2.jpg"));
    loginBtn->setIconSize(QSize(290,40));
    loginBtn->setFlat(true);
    loginBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
}

void LoginWidget::LoginSlot()
{
    //向服务器发送请求登录包，
    //解析应答包，若成功则设置界面的播放记录模块的显示
    //如失败则有错误判断

    QString UserName = usernameEdit->text();
    QString UserPwd = passwordEdit->text();

    login_pack.Login(UserName,UserPwd);
    tcpClient->write(login_pack.getData(),login_pack.getSize());
    qDebug("----------发包");

    timerRead->start(500);


}

void LoginWidget::PacketReadSlot()
{

    if(!loginFlag)
    {
        tcpClient->read(login_pack_ret.getData(),login_pack_ret.getSize());
        login_pack_ret.unpack();
    qDebug("----------解包");
        login_ret_t *pData = (login_ret_t *)login_pack_ret.getBody();
        qDebug("ret=%d",pData->ret);
        if(pData->ret==1)
        {
            emit LoginSuccessSignal(true);
            this->close();
            loginFlag=true;
        }
        else if(pData->ret==666)
        {
            qDebug()<<"登录失败！！";
        }
        else
        {
            qDebug()<<"error！！";
        }
    }


}

void LoginWidget::ConnectInit()
{
    timerRead = new QTimer();
    connect(loginBtn,SIGNAL(released()),this,SLOT(LoginSlot()));
    connect(timerRead,SIGNAL(timeout()),this,SLOT(PacketReadSlot()));
    connect(closeBtn,SIGNAL(released()),this,SLOT(close()));
}
