#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QToolButton>
#include <QAction>
#include <QHBoxLayout>
#include <QRect>
#include <QTcpSocket>
#include "TitleBar.h"
#include "LoginWidget.h"
#include "content/ContentWidget.h"
#include "../videoPlay/ffvideoplayer.h"
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:

public slots:
    void VidePlaySlot();
    void UserLoginSlot();
    void VideoWidgetShowSlot();
    void VideoLibWidgetShowSlot();
    void VideoPlaySlot();
    void LoginSuccessSLot(bool loginFlag);



public:
    TitleBar *titleBar;
    ContentWidget *contentWidget;
    LoginWidget *loginWidget;

private:
    QLabel *backgoundLab;
    bool loginFlag;

    void UiInit();
    void ConnectInit();

};

#endif // MAINWIDGET_H
