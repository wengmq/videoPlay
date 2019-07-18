#include <QtGui/QApplication>
#include "videoClient.h"
#include"ClientLogin.h"
#include <QTextCodec> //编码
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置本地编码 头文件 #include <QTextCodec> //编码
    QTextCodec *codec = QTextCodec::codecForLocale();
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    ClientLogin w;
    w.show();

    return a.exec();
}
