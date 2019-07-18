#include "ContentBottomWidget.h"

ContentBottomWidget::ContentBottomWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(0,40,1000,503);
    contentBottomWidgetTitleBar = new ContentBottomWidgetTitleBar(this);
    videoWidget = new CW_VideoWidget(this);
    videoLibWidget= new CW_VideoLibWidget(this);
    videoLibWidget->hide();
}
