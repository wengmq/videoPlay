#include "CW_VideoLibWidgetLeft.h"

CW_VideoLibWidgetLeft::CW_VideoLibWidgetLeft(QWidget *parent)
    :QFrame(parent)
{
    setMouseTracking(true);
    UiInit();
}

void CW_VideoLibWidgetLeft::UiInit()
{
    setStyleSheet(::main_style5);

    setMinimumSize(200,450);
    setMaximumSize(720,450);
}
