#include "ClientLogin.h"

ClientLogin::ClientLogin(QWidget *parent) :
    QWidget(parent)
{

    //���ñ��ر��� ͷ�ļ� #include <QTextCodec> //����
//    QTextCodec *codec = QTextCodec::codecForLocale();
//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
    this->setFixedSize(648,584);

   // this->setWindowIcon(QIcon("MyPlane/images/game.ico"));

    //���ô��ھ��� ͷ�ļ������� #include <QtGui/QApplication>  #include <QDesktopWidget>
    this->move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/4);
//    this->setWindowFlags(Qt::FramelessWindowHint);//ȥ�߿�
//    this->setAttribute(Qt::WA_TranslucentBackground,true);//���ô���͸��

    //���ñ���ͼƬ
//    QPalette palatte;
//    palatte.setBrush(QPalette::Background,QBrush(QPixmap("bg_login.jpg")));
//    this->setPalette(palatte);


    NameLine = new QLineEdit(this);
    NameLine->setGeometry(275,175,192,28);
    NameLine->setPlaceholderText(QObject::tr("�������˺�"));

    PwdLine = new QLineEdit(this);
    PwdLine->setGeometry(275,225,192,28);
    PwdLine->setEchoMode(QLineEdit::Password);//��������
    PwdLine->setPlaceholderText("����������");

    IpLine = new QLineEdit(this);
    IpLine->setGeometry(275,275,192,28);
    IpLine->setPlaceholderText("������IP��ַ");

    PortLine = new QLineEdit(this);
    PortLine->setGeometry(275,325,192,28);
    PortLine->setPlaceholderText("������˿ں�");
    QLabel *NameLabel = new QLabel(QObject::tr("�˺�: "),this);
    NameLabel->setGeometry(175,175,100,28);

    QLabel *PwdLabel = new QLabel("����: ",this);
    PwdLabel->setGeometry(175,225,100,28);

    QLabel *IpLabel = new QLabel("IP��ַ: ",this);
    IpLabel->setGeometry(175,275,100,28);

    QLabel *PortLabel = new QLabel("�˿ں�: ",this);
    PortLabel->setGeometry(175,325,100,28);

    TipLabel = new QLabel(this);
    TipLabel->setGeometry(100,500,400,56);

    QFont ft;//���������С
    ft.setPointSize(14);
    PwdLine->setFont(ft);
    NameLine->setFont(ft);
    IpLine->setFont(ft);
    PortLine->setFont(ft);

    QPalette pa; //����������ɫ
    pa.setColor(QPalette::WindowText,Qt::black);
    PwdLine->setPalette(pa);
    NameLine->setPalette(pa);


    sureBtn = new QPushButton(this);
    sureBtn->setGeometry(150,400,159,56);
    sureBtn->setText("��¼");


    backBtn = new QPushButton(this);
    backBtn->setGeometry(340,400,159,56);
    backBtn->setText("����");






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
            TipLabel->setText("���ӷ������ɹ�");
            sureBtn->setText("ȡ����¼");
        }
        connectFlag = !connectFlag;

        //����
        m_pack.Login(NameLine->text(),PwdLine->text());

        qDebug()<<"m_pack.getSize():"<< m_pack.getSize();
         tcpClient->write(m_pack.getData(), m_pack.getSize());
         qDebug()<<"1111111111111111";
//         Sleep(2000);



         timerRead->start(500);//����������������ʱ������ʱ���Ϊ500���롣



    }
    else
    {
        tcpClient->disconnectFromHost();
        tcpClient->waitForDisconnected(1000);
        if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))
        {
            TipLabel->setText("�Ͽ����ӳɹ�");
            sureBtn->setText("��¼");
            timerRead->stop();
        }
        connectFlag = !connectFlag;

    }

}

void ClientLogin::Init()
{

    tcpClient=new QTcpSocket(this);
    tcpClient->abort();//ȡ��ԭ������

    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(ReadError(QAbstractSocket::SocketError)));
}

void ClientLogin::ReadError(QAbstractSocket::SocketError)
{
    tcpClient->disconnectFromHost();

    TipLabel->setText(tr("���ӷ�����ʧ��,ԭ��:%1").arg(tcpClient->errorString()));
}
void ClientLogin::retPacketRead()
{

    //���
    qDebug()<<"m_pack_ret.getSize():"<< m_pack_ret.getSize();
    tcpClient->read(m_pack_ret.getData(), m_pack_ret.getSize());
    qDebug()<<"m_pack_ret.getSize():"<< m_pack_ret.getSize();

    m_pack_ret.unpack();
    Login_ret_t *pData = (Login_ret_t *)m_pack_ret.getBody();
    qDebug()<<"pData->ret"<<pData->ret;
    if(pData->ret == 1)
    {
        qDebug()<<"�˺�������ȷ����¼�ɹ�";


        w.show();
        this->hide();
    }
    else if(pData->ret ==666)
    {
        qDebug()<<"��¼ʧ�ܣ���";
        //qDebug()<<m_pack.getHeader()->optid;
    }
    else
    {
        qDebug()<<"error����";
        //qDebug()<<m_pack.getHeader()->optid;
    }

}

