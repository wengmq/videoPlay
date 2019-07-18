#include "videoClient.h"
#include "ui_videoClient.h"

videoClient::videoClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::videoClient)
{
    ui->setupUi(this);
}

videoClient::~videoClient()
{
    delete ui;
}
