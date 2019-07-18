#include "CW_VideoLibWidgetRight.h"

CW_VideoLibWidgetRight::CW_VideoLibWidgetRight(QWidget *parent)
    :QFrame(parent)
{
    setMouseTracking(true);
    UiInit();
}

void CW_VideoLibWidgetRight::UiInit()
{
    setStyleSheet(::main_style6);

    setMinimumSize(780,450);
    setMaximumSize(1200,450);
}
