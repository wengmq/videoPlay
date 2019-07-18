#include "CW_VideoLibWidget.h"

CW_VideoLibWidget::CW_VideoLibWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(0,40,1000,463);
    totalLayout = new QHBoxLayout(this);
    videoLibWidgetLeft = new CW_VideoLibWidgetLeft;
    videoLibWidgetRight = new CW_VideoLibWidgetRight;
    totalLayout->addWidget(videoLibWidgetLeft);
    totalLayout->addSpacing(0);
    totalLayout->addWidget(videoLibWidgetRight);
}
