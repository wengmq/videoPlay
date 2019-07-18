#ifndef CW_VIDEOWIDGET_H
#define CW_VIDEOWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CW_VideoWidgetUpper.h"
#include "CW_VideoWidgetLower.h"
class CW_VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CW_VideoWidget(QWidget *parent = 0);

signals:

public slots:

public:
    CW_VideoWidgetUpper *videoWidgetUpper;
    CW_VideoWidgetLower *videoWidgetLower;
private:
    QVBoxLayout *totalLayout;
};

#endif // CW_VIDEOWIDGET_H
