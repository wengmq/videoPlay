/********************************************************************************
** Form generated from reading UI file 'videoClient.ui'
**
** Created: Mon Jun 17 00:54:20 2019
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOCLIENT_H
#define UI_VIDEOCLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_videoClient
{
public:
    QLabel *label;

    void setupUi(QWidget *videoClient)
    {
        if (videoClient->objectName().isEmpty())
            videoClient->setObjectName(QString::fromUtf8("videoClient"));
        videoClient->resize(400, 300);
        label = new QLabel(videoClient);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 30, 72, 15));

        retranslateUi(videoClient);

        QMetaObject::connectSlotsByName(videoClient);
    } // setupUi

    void retranslateUi(QWidget *videoClient)
    {
        videoClient->setWindowTitle(QApplication::translate("videoClient", "videoClient", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("videoClient", "\346\265\213\350\257\225\347\225\214\351\235\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class videoClient: public Ui_videoClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOCLIENT_H
