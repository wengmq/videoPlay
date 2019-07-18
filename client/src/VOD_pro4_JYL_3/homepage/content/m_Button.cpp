#include "m_Button.h"
#include <QDebug>
#include <string.h>
m_Button::m_Button(QWidget *parent)
    :QPushButton(parent)
{

}

void m_Button::setChannelMsg(int count,int id,const char* name)
{
    channel_count = count;
    channel_id = id;

    strcpy(channel_name,name);

    qDebug("ÉèÖÃ°´Å¥Ãû³Æ");
    QString str = QString::fromUtf8(name);
    this->setText(str);

}
