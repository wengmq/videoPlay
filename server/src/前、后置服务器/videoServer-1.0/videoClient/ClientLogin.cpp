#include "ClientLogin.h"

ClientLogin::ClientLogin(QWidget *parent) :
    QWidget(parent)
{

    //设置本地编码 头文件 #include <QTextCodec> //编码
//    QTextCodec *codec = QTextCodec::codecForLocale();
//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
    this->setFixedSize(648,584);

   // this->setWindowIcon(QIcon("MyPlane/images/game.ico"));

    //设置窗口居中 头文件包含： #include <QtGui/QApplication>  #include <QDesktopWidget>
    this->move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/4);
//    this->setWindowFlags(Qt::FramelessWindowHint);//去边框
//    this->setAttribute(Qt::WA_TranslucentBackground,true);//设置窗口透明

    //设置背景图片
//    QPalette palatte;
//    palatte.setBrush(QPalette::Background,QBrush(QPixmap("bg_login.jpg")));
//    this->setPalette(palatte);


    NameLine = new QLineEdit(this);
    NameLine->setGeometry(275,175,192,28);
    NameLine->setPlaceholderText(QObject::tr("请输入账号"));

    PwdLine = new QLineEdit(this);
    PwdLine->setGeometry(275,225,192,28);
    PwdLine->setEchoMode(QLineEdit::Password);//设置密文
    PwdLine->setPlaceholderText("请输入密码");

    IpLine = new QLineEdit(this);
    IpLine->setGeometry(275,275,192,28);
    IpLine->setPlaceholderText("请输入IP地址");

    PortLine = new QLineEdit(this);
    PortLine->setGeometry(275,325,192,28);
    PortLine->setPlaceholderText("请输入端口号");
    QLabel *NameLabel = new QLabel(QObject::tr("账号: "),this);
    NameLabel->setGeometry(175,175,100,28);

    QLabel *PwdLabel = new QLabel("密码: ",this);
    PwdLabel->setGeometry(175,225,100,28);

    QLabel *IpLabel = new QLabel("IP地址: ",this);
    IpLabel->setGeometry(175,275,100,28);

    QLabel *PortLabel = new QLabel("端口号: ",this);
    PortLabel->setGeometry(175,325,100,28);

    TipLabel = new QLabel(this);
    TipLabel->setGeometry(100,500,400,56);

    QFont ft;//控制字体大小
    ft.setPointSize(14);
    PwdLine->setFont(ft);
    NameLine->setFont(ft);
    IpLine->setFont(ft);
    PortLine->setFont(ft);

    QPalette pa; //控制字体颜色
    pa.setColor(QPalette::WindowText,Qt::black);
    PwdLine->setPalette(pa);
    NameLine->setPalette(pa);


    sureBtn = new QPushButton(this);
    sureBtn->setGeometry(150,400,159,56);
    sureBtn->setText("登录");


    backBtn = new QPushButton(this);
    backBtn->setGeometry(340,400,159,56);
    backBtn->setText("返回");






    FormHelper::FormInCenter(this);
    FormHelper::FormNotResize(this);

    this->Init();

    connectFlag = 0;

     this->connect(sureBtn,SIGNAL(clicked()),this,SLOT(sureBtn_clicked()));

    timerRead = new QTimer(this);
    connect(timerRead,SIGNAL(timeout()),this,SLOT(retPacketRead()));
}
void ClientLogin::sureBtn_clicked()
{
    if (!connectFlag)//not connect
    {
        tcpClient->connectToHost(IpLine->text(),PortLine->text().toInt());
        if (tcpClient->waitForConnected(1000))
        {
            TipLabel->setText("连接服务器成功");
            sureBtn->setText("取消登录");
        }
        connectFlag = !connectFlag;

        //发包
        m_pack.Login(NameLine->text(),PwdLine->text());

        qDebug()<<"m_pack.getSize():"<< m_pack.getSize();
         tcpClient->write(m_pack.getData(), m_pack.getSize());
         qDebug()<<"1111111111111111";
//         Sleep(2000);



         timerRead->start(500);//启动或重新启动计时器，超时间隔为500毫秒。



    }
    else
    {
        tcpClient->disconnectFromHost();
        tcpClient->waitForDisconnected(1000);
        if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))
        {
            TipLabel->setText("断开连接成功");
            sureBtn->setText("登录");
            timerRead->stop();
        }
        connectFlag = !connectFlag;

    }

}

void ClientLogin::Init()
{

    tcpClient=new QTcpSocket(this);
    tcpClient->abort();//取消原有连接

    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));
}

void ClientLogin::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();

    TipLabel->setText(tr("连接服务器失败,原因:%1").arg(tcpClient->errorString()));
}
void ClientLogin::retPacketRead()
{

    //解包
    qDebug()<<"m_pack_ret.getSize():"<< m_pack_ret.getSize();
    tcpClient->read(m_pack_ret.getData(), m_pack_ret.getSize());
    qDebug()<<"m_pack_ret.getSize():"<< m_pack_ret.getSize();

    m_pack_ret.unpack();
    Login_ret_t *pData = (Login_ret_t *)m_pack_ret.getBody();
    qDebug()<<"pData->ret"<<pData->ret;
    if(pData->ret == 1)
    {
        qDebug()<<"账号密码正确，登录成功";


        w.show();
        this->hide();
    }
    else if(pData->ret ==666)
    {
        qDebug()<<"登录失败！！";
        //qDebug()<<m_pack.getHeader()->optid;
    }
    else
    {
        qDebug()<<"error！！";
        //qDebug()<<m_pack.getHeader()->optid;
    }

}

