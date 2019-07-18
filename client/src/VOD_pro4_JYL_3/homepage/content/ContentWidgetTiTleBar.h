#ifndef CONTENTWIDGETTITLEBAR_H
#define CONTENTWIDGETTITLEBAR_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include "m_Button.h"
#include "../../packet/PublicPacket.h"


const QString main_style1 = "QFrame{background:rgb(255,255,255);}";

#pragma pack(push)
#pragma pack(1)

class ContentWidgetTiTleBar: public QFrame
{
    Q_OBJECT
public:
    explicit ContentWidgetTiTleBar(QWidget *parent =0);
    ~ContentWidgetTiTleBar(){}

signals:
    void channelBtnSignal(int channelId);
public slots:
    void  channelBtnSlot(int channelId);

public:
    void setChannleData(QList<reply_channel_t > dataList);

    QLabel *lineLab;

//    QPushButton *teleplayBtn;
//    QPushButton *varietyBtn;
//    QPushButton *movieBtn;
//    QPushButton *cartoonBtn;


    QPushButton *mineBtn;
    QPushButton *historyBtn;
    QPushButton *collectBtn;
    QPushButton *downloadBtn;

private:

    QList<m_Button *> channel_btn_list;
    QList<reply_channel_t> channel_data_list;

    QHBoxLayout *titleLayout;
    QHBoxLayout *leftLayout;
    QHBoxLayout *rightLayout;

    void TitleInit();
};

#pragma pack(pop)
#endif // CONTENTWIDGETTITLEBAR_H
