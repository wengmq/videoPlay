#ifndef CLIENTLOGIN_H
#define CLIENTLOGIN_H

#include <QWidget>
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QPushButton>
#include <QPalette>
#include <QIcon>
#include <QMessageBox>
#include <QRegExpValidator>
#include<QRegExp>
#include <QMouseEvent>
#include<QPainter>
#include "myhelper.h"
#include <QTcpSocket>
#include "CBasePacket.h"
#include "public.h"
#include "VideoPacket.h"
#include "videoClient.h"
#include <windows.h>
#include<QTimer>
class ClientLogin : public QWidget
{
    Q_OBJECT
public:
    explicit ClientLogin(QWidget *parent = 0);



signals:
     void ReturnLoginSignal();

public slots:
     void sureBtn_clicked();

     void ReadError(QAbstractSocket::SocketError);
     void retPacketRead();

private:
    QLineEdit *NameLine;
    QLineEdit *PwdLine;
    QLineEdit *IpLine;
    QLineEdit *PortLine;
    QPushButton *sureBtn;
    QPushButton *backBtn;
    QPushButton *forgetPwdBtn;
    QPushButton *closeBtn;

    QLabel *TipLabel;

    QTcpSocket *tcpClient;

    void Init();

    int connectFlag;

    VideoPacket m_pack;//要发送的数据包
     VideoPacket m_pack_ret;//要接收服务端的应答数据包
    videoClient w;
     QTimer *timerRead;
};

#endif // CLIENTLOGIN_H
