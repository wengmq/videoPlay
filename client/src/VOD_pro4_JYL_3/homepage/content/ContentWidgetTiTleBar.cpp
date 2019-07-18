#include "ContentWidgetTiTleBar.h"
#include <QMenu>
#include <QFile>
#include <QDebug>
ContentWidgetTiTleBar::ContentWidgetTiTleBar(QWidget *parent)
    : QFrame(parent)
{
    setMouseTracking(true);
    //TitleInit();
}

void ContentWidgetTiTleBar::TitleInit()
{
    setStyleSheet(::main_style1);

    setMinimumSize(1000,40);
    setMaximumSize(1920,40);


    titleLayout = new QHBoxLayout(this);
    leftLayout = new QHBoxLayout;

    int channel_count  = channel_data_list.count();
    qDebug("channel=%d",channel_count);

    if(channel_count>0)
    {
        for(int i=0; i<channel_count;i++)
        {
            m_Button *btn = new m_Button(this);
            qDebug("======创建频道按钮=====");
            btn->setChannelMsg(channel_data_list.at(i).channel_count,channel_data_list.at(i).channel_id,channel_data_list.at(i).channel_name);
            btn->setFlat(true);
            btn->setCursor(Qt::PointingHandCursor);
            channel_btn_list.append(btn);
        }
    }
    else
    {
        qDebug("======无频道分类=====");
    }

    if(channel_btn_list.count()>0)
    {
        for(int i=0;i<channel_btn_list.count();i++)
        {
            qDebug("======添加到布局管理器=====");
            if(channel_btn_list.count()<5)
            {
                leftLayout->addSpacing(50);
            }
            else
            {
                leftLayout->addSpacing(10);
            }

            leftLayout->addWidget(channel_btn_list.at(i));
        }

    }



//    teleplayBtn= new QPushButton;
//    teleplayBtn->setFixedSize(60,36);
//    teleplayBtn->setIcon(QIcon("../image/btn/type/teleplay.jpg"));
//    teleplayBtn->setIconSize(QSize(60,36));
//    teleplayBtn->setFlat(true);
//    teleplayBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
//    //teleplayBtn->setDisabled(true);
//    teleplayBtn->setCursor(Qt::PointingHandCursor);

//    varietyBtn= new QPushButton;
//    varietyBtn->setFixedSize(50,36);
//    varietyBtn->setIcon(QIcon("../image/btn/type/variety.jpg"));
//    varietyBtn->setIconSize(QSize(50,36));
//    varietyBtn->setFlat(true);
//    varietyBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
//    //varietyBtn->setDisabled(true);
//    varietyBtn->setCursor(Qt::PointingHandCursor);

//    movieBtn= new QPushButton;
//    movieBtn->setFixedSize(50,36);
//    movieBtn->setIcon(QIcon("../image/btn/type/movie.jpg"));
//    movieBtn->setIconSize(QSize(50,36));
//    movieBtn->setFlat(true);
//    movieBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
//    //movieBtn->setDisabled(true);
//    movieBtn->setCursor(Qt::PointingHandCursor);

//    cartoonBtn= new QPushButton;
//    cartoonBtn->setFixedSize(50,36);
//    cartoonBtn->setIcon(QIcon("../image/btn/type/cartoon.jpg"));
//    cartoonBtn->setIconSize(QSize(50,36));
//    cartoonBtn->setFlat(true);
//    cartoonBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
//    //cartoonBtn->setDisabled(true);
//    cartoonBtn->setCursor(Qt::PointingHandCursor);


    //    leftLayout->addSpacing(50);
    //    leftLayout->addWidget(teleplayBtn);
    //    leftLayout->addSpacing(50);
    //    leftLayout->addWidget(varietyBtn);
    //    leftLayout->addSpacing(50);
    //    leftLayout->addWidget(movieBtn);
    //    leftLayout->addSpacing(50);
    //    leftLayout->addWidget(cartoonBtn);




     rightLayout = new QHBoxLayout;

     mineBtn = new QPushButton;
     mineBtn->setFixedSize(60,36);
     mineBtn->setIcon(QIcon("../image/btn/type/mine.jpg"));
     mineBtn->setIconSize(QSize(60,36));
     mineBtn->setFlat(true);
     mineBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
     //mineBtn->setDisabled(true);
     mineBtn->setCursor(Qt::PointingHandCursor);

     historyBtn= new QPushButton;
     historyBtn->setFixedSize(60,36);
     historyBtn->setIcon(QIcon("../image/btn/type/history.jpg"));
     historyBtn->setIconSize(QSize(60,36));
     historyBtn->setFlat(true);
     historyBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
     //historyBtn->setDisabled(true);
     historyBtn->setCursor(Qt::PointingHandCursor);

     collectBtn= new QPushButton;
     collectBtn->setFixedSize(60,36);
     collectBtn->setIcon(QIcon("../image/btn/type/collect.jpg"));
     collectBtn->setIconSize(QSize(60,36));
     collectBtn->setFlat(true);
     collectBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
     //collectBtn->setDisabled(true);
     collectBtn->setCursor(Qt::PointingHandCursor);

     downloadBtn= new QPushButton;
     downloadBtn->setFixedSize(60,36);
     downloadBtn->setIcon(QIcon("../image/btn/type/download.jpg"));
     downloadBtn->setIconSize(QSize(60,36));
     downloadBtn->setFlat(true);
     downloadBtn->setStyleSheet("QPushButton{background-color:transparent;border:0px;color:white}");
     //downloadBtn->setDisabled(true);
     downloadBtn->setCursor(Qt::PointingHandCursor);

     rightLayout->setSpacing(20);
     rightLayout->addWidget(mineBtn);
     rightLayout->addSpacing(20);
     rightLayout->addWidget(historyBtn);
     rightLayout->addSpacing(20);
     rightLayout->addWidget(collectBtn);
     rightLayout->addSpacing(20);
     rightLayout->addWidget(downloadBtn);


     titleLayout->addLayout(leftLayout);
     //titleLayout->addSpacing(20);
     titleLayout->addStretch();
     titleLayout->addLayout(rightLayout);

//     totalLayout->addLayout(lineLayout);
//     totalLayout->addLayout(titleLayout);

}

void ContentWidgetTiTleBar::setChannleData(QList<reply_channel_t > dataList)
{
    channel_data_list = dataList;
    TitleInit();
}

 void  ContentWidgetTiTleBar::channelBtnSlot(int channelId)
 {
//     switch(channelId)
//     {

//     }
 }
