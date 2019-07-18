#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QtGui/QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QString>
#include <QTcpSocket>
#include <QTimer>
#include "../packet/VideoPacket.h"
#include "../packet/PublicPacket.h"

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

signals:
    void LoginSuccessSignal(bool loginFlag);

public slots:
    void LoginSlot();
    void PacketReadSlot();

private:
    QLabel *backgoundLab;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginBtn;
    QPushButton *closeBtn;

    bool loginFlag;
    VideoPacket login_pack;//��¼�������ݰ�
    VideoPacket login_pack_ret;//��¼Ӧ�����ݰ�

    QTimer *timerRead;






    void UiInit();
    void ConnectInit();

};

#endif // LOGINWIDGET_H

