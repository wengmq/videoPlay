#ifndef CW_VIDEOLIBWIDGETLEFT_H
#define CW_VIDEOLIBWIDGETLEFT_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

const QString main_style5 = "QFrame{background:rgb(255,0,0);}";

#pragma pack(push)
#pragma pack(1)

class CW_VideoLibWidgetLeft:public QFrame
{
public:
    explicit CW_VideoLibWidgetLeft(QWidget *parent=0);
    ~CW_VideoLibWidgetLeft(){}

private:
    void UiInit();

};
#pragma pack(pop)

#endif // CW_VIDEOLIBWIDGETLEFT_H
