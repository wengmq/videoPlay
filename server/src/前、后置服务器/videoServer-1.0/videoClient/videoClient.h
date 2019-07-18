#ifndef VIDEOCLIENT_H
#define VIDEOCLIENT_H

#include <QWidget>

namespace Ui {
    class videoClient;
}

class videoClient : public QWidget
{
    Q_OBJECT

public:
    explicit videoClient(QWidget *parent = 0);
    ~videoClient();

private:
    Ui::videoClient *ui;
};

#endif // VIDEOCLIENT_H
