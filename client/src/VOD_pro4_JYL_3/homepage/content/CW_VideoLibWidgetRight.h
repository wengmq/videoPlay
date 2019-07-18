#ifndef CW_VIDEOLIBWIDGETRIGHT_H
#define CW_VIDEOLIBWIDGETRIGHT_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

const QString main_style6 = "QFrame{background:rgb(0,255,0);}";

#pragma pack(push)
#pragma pack(1)

class CW_VideoLibWidgetRight:public QFrame
{
public:
    explicit CW_VideoLibWidgetRight(QWidget *parent = 0);
    ~CW_VideoLibWidgetRight(){}

private:
    void UiInit();

};

#pragma pack(pop)

#endif // CW_VIDEOLIBWIDGETRIGHT_H
