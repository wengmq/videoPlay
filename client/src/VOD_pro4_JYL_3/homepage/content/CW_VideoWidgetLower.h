#ifndef CW_VIDEOWIDGETLOWER_H
#define CW_VIDEOWIDGETLOWER_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QToolButton>
#include <QAction>

#include "m_ToolButton.h"
#include "../../packet/PublicPacket.h"

const QString main_style3 = "QFrame{background:rgb(255,255,255);}";

#pragma pack(push)
#pragma pack(1)

class CW_VideoWidgetLower: public QFrame
{
    Q_OBJECT
public:
    explicit CW_VideoWidgetLower(QWidget *parent =0);
    ~CW_VideoWidgetLower(){}

signals:
    void videoPlaySignal(const char video_name[]);


public slots:
    void videoPlaySignalEmitSlot();
    void videoPlaySlot();


//    QToolButton *videoBtn1;
//    QToolButton *videoBtn2;
//    QToolButton *videoBtn3;
//    QToolButton *videoBtn4;
//    QToolButton *videoBtn5;
//    QToolButton *videoBtn6;

    //QAction *pAction;
     void setVideoData(QList<video_list_t > dataList);


private:
    void UiInit();
    QHBoxLayout * videoLagout;

    QList<m_ToolButton *> video_btn_list;
    QList<video_list_t > video_data_list;

};

#pragma pack(pop)
#endif // CW_VIDEOWIDGETLOWER_H
