#include <QtGui/QApplication>
#include "videoClient.h"
#include"ClientLogin.h"
#include <QTextCodec> //����
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //���ñ��ر��� ͷ�ļ� #include <QTextCodec> //����
    QTextCodec *codec = QTextCodec::codecForLocale();
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    ClientLogin w;
    w.show();

    return a.exec();
}
