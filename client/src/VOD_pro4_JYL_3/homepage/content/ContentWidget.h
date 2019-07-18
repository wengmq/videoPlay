#ifndef CONTENTWIDGET_H
#define CONTENTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "ContentWidgetTiTleBar.h"
#include "ContentBottomWidget.h"

class ContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentWidget(QWidget *parent = 0);

signals:

public slots:

public:
    //QLabel *label;
    ContentWidgetTiTleBar *contentWidgetTiTleBar;
    ContentBottomWidget *contentBottomWidget;
};

#endif // CONTENTWIDGET_H
