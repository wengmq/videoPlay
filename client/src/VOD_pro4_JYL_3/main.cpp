#include <QtGui/QApplication>
#include "ServerConnectWidget.h"
#include <QTextCodec>
#include <QTcpSocket>
#include <QTimer>
#include "homepage/MainWidget.h"
#include "packet/PublicPacket.h"
#include <QList>
QTcpSocket *tcpClient = new QTcpSocket();
QString RtspServerAddr;
//QTimer *timerRead = new QTimer();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //…Ë÷√±æµÿ±‡¬Î
    QTextCodec *codec = QTextCodec::codecForLocale();
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    ServerConnectWidget w;
    w.show();

    return a.exec();
}
