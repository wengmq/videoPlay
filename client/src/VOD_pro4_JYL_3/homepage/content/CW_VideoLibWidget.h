#ifndef CW_VIDEOLIBWIDGET_H
#define CW_VIDEOLIBWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CW_VideoLibWidgetLeft.h"
#include "CW_VideoLibWidgetRight.h"

class CW_VideoLibWidget: public QWidget
{
    Q_OBJECT
public:
    explicit CW_VideoLibWidget(QWidget *parent = 0);

private:
    CW_VideoLibWidgetLeft *videoLibWidgetLeft;
    CW_VideoLibWidgetRight *videoLibWidgetRight;
    QHBoxLayout *totalLayout;
};

#endif // CW_VIDEOLIBWIDGET_H
