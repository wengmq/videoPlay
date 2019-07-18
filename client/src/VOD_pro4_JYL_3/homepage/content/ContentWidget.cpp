#include "ContentWidget.h"

ContentWidget::ContentWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setGeometry(0,45,1000,543);

    contentWidgetTiTleBar = new ContentWidgetTiTleBar(this);
    contentBottomWidget = new ContentBottomWidget(this);

}
