#include "CW_VideoWidget.h"

CW_VideoWidget::CW_VideoWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(0,40,1000,463);
    totalLayout = new QVBoxLayout(this);
    videoWidgetUpper = new CW_VideoWidgetUpper;
    videoWidgetLower = new CW_VideoWidgetLower;
    totalLayout->addWidget(videoWidgetUpper);
    totalLayout->addSpacing(5);
    totalLayout->addWidget(videoWidgetLower);
}
