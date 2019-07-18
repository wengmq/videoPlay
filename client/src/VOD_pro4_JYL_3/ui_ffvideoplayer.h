/********************************************************************************
** Form generated from reading UI file 'ffvideoplayer.ui'
**
** Created: Tue Jun 25 19:48:44 2019
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFVIDEOPLAYER_H
#define UI_FFVIDEOPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <m_label.h>

QT_BEGIN_NAMESPACE

class Ui_FFVideoPlayer
{
public:
    m_Label *videoShow_Lab;
    QPushButton *play_Btn;
    QSlider *timeSlider;
    QLabel *curr_Time_Lab;
    QLabel *total_Time_Lab;

    void setupUi(QDialog *FFVideoPlayer)
    {
        if (FFVideoPlayer->objectName().isEmpty())
            FFVideoPlayer->setObjectName(QString::fromUtf8("FFVideoPlayer"));
        FFVideoPlayer->resize(670, 435);
        videoShow_Lab = new m_Label(FFVideoPlayer);
        videoShow_Lab->setObjectName(QString::fromUtf8("videoShow_Lab"));
        videoShow_Lab->setGeometry(QRect(0, 0, 671, 381));
        videoShow_Lab->setFrameShape(QFrame::Box);
        play_Btn = new QPushButton(FFVideoPlayer);
        play_Btn->setObjectName(QString::fromUtf8("play_Btn"));
        play_Btn->setEnabled(true);
        play_Btn->setGeometry(QRect(40, 390, 38, 38));
        QFont font;
        font.setPointSize(14);
        play_Btn->setFont(font);
        play_Btn->setAutoDefault(true);
        timeSlider = new QSlider(FFVideoPlayer);
        timeSlider->setObjectName(QString::fromUtf8("timeSlider"));
        timeSlider->setGeometry(QRect(190, 400, 381, 16));
        timeSlider->setOrientation(Qt::Horizontal);
        curr_Time_Lab = new QLabel(FFVideoPlayer);
        curr_Time_Lab->setObjectName(QString::fromUtf8("curr_Time_Lab"));
        curr_Time_Lab->setGeometry(QRect(100, 400, 81, 20));
        QFont font1;
        font1.setPointSize(12);
        curr_Time_Lab->setFont(font1);
        curr_Time_Lab->setFrameShape(QFrame::StyledPanel);
        total_Time_Lab = new QLabel(FFVideoPlayer);
        total_Time_Lab->setObjectName(QString::fromUtf8("total_Time_Lab"));
        total_Time_Lab->setGeometry(QRect(580, 400, 81, 16));
        total_Time_Lab->setFont(font1);
        total_Time_Lab->setFrameShape(QFrame::StyledPanel);

        retranslateUi(FFVideoPlayer);

        QMetaObject::connectSlotsByName(FFVideoPlayer);
    } // setupUi

    void retranslateUi(QDialog *FFVideoPlayer)
    {
        FFVideoPlayer->setWindowTitle(QApplication::translate("FFVideoPlayer", "Dialog", 0, QApplication::UnicodeUTF8));
        videoShow_Lab->setText(QString());
        play_Btn->setText(QString());
        curr_Time_Lab->setText(QString());
        total_Time_Lab->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FFVideoPlayer: public Ui_FFVideoPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFVIDEOPLAYER_H
