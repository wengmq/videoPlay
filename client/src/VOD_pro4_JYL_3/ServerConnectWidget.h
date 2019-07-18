#ifndef SERVERCONNECTWIDGET_H
#define SERVERCONNECTWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTcpSocket>
#include <QTimer>
#include <QList>
#include <string.h>
#include "homepage/MainWidget.h"
#include "./packet/PublicPacket.h"
#include "./packet/VideoPacket.h"
class ServerConnectWidget : public QWidget
{
    Q_OBJECT

public:
    ServerConnectWidget(QWidget *parent = 0);
    ~ServerConnectWidget();

public slots:
    void ConnectSlot();
    void ChannelPacketReadSlot();


private:
    QLabel  *backgroundLab;

    QLineEdit *ipEdit;
    QLineEdit *portEdit;
    QPushButton *connectBtn;
    QPushButton *closeBtn;

    reply_channel_t  pData;

    video_list_t pData1;

    bool connectFlag;
    bool channelFlag;
    MainWidget *mainWidget;

    VideoPacket channel_pack;//Ƶ�������������ݰ�
    VideoPacket video_pack;//��Ƶ�б��������ݰ�

    VideoPacket pack_ret;//Ƶ������Ӧ�����ݰ�
    QTimer *timeRead;//��ʱ��ȡ�հ�

    QList<reply_channel_t > channel_data;
    QList<video_list_t > video_data;

    int channelTotalCount;
    int channelCount;

    int videoCount;
    int videoTotalCount;

    void UiInit();
    void ConnectInit();
};

#endif // SERVERCONNECTWIDGET_H
