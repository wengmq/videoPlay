#ifndef CONTENTBOTTOMWIDGET_H
#define CONTENTBOTTOMWIDGET_H

#include <QWidget>
#include "ContentBottomWidgetTitleBar.h"
#include "CW_VideoWidget.h"
#include "CW_VideoLibWidget.h"
class ContentBottomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContentBottomWidget(QWidget *parent = 0);

signals:

public slots:

public:
    ContentBottomWidgetTitleBar *contentBottomWidgetTitleBar;

    CW_VideoWidget *videoWidget;
    CW_VideoLibWidget *videoLibWidget;
};

#endif // CONTENTBOTTOMWIDGET_H
