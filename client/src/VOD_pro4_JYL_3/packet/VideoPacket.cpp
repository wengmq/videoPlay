#include "VideoPacket.h"

VideoPacket::VideoPacket()
            :BasePacket(sizeof(packet_all_st))
{
     memset(&m_head, 0, sizeof(m_head));
}
VideoPacket:: ~VideoPacket()
{


}
bool VideoPacket::pack()
{
   memcpy(m_data, &this->m_head, sizeof(packet_header_t));
   memcpy(m_data+sizeof(packet_header_t), this->m_Body, sizeof(m_Body));
   return true;
}

bool VideoPacket::unpack()
{
   memcpy(&this->m_head, m_data, sizeof(packet_header_t));
   memcpy(this->m_Body, m_data+sizeof(packet_header_t), sizeof(m_Body));
   qDebug()<<"m_head.optid:"<<this->m_head.optid;
   return true;
}

bool VideoPacket::Heartbeat()
{
    //填充包头
    m_head.funid = 0x00; //心跳
    m_head.optid = 0x00; //请求
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    return this->pack();
}

bool VideoPacket::Login(QString name,QString pwd)
{
    //填充包头
    m_head.funid = 0x01; //login
    m_head.optid = 0x00; //登录请求
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    //填充包体
    Login_t *body = (Login_t*)m_Body;
    QByteArray qByteArrayName = name.toUtf8();
    QByteArray qByteArrayPwd = pwd.toUtf8();

    strcpy(body->user, qByteArrayName.data());
    strcpy(body->pwd, qByteArrayPwd.data());

    return this->pack();
}

bool VideoPacket::RequestChannel()
{
    //填充包头
    m_head.funid = 0x02; //频道请求包功能号
    m_head.optid = 0x00; //频道分类请求
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    return this->pack();
}

bool VideoPacket::RequestType()
{
    //填充包头
    m_head.funid = 0x04; //视频请求包功能号
    m_head.optid = 0x00; //视频类型分类请求
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    return this->pack();
}

bool VideoPacket::RequestVideoList(int channelId)
{
    //填充包头
    m_head.funid = 0x03; //视频请求包功能号
    m_head.optid = channelId; //视频频道
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    return this->pack();
}

packet_header_t* VideoPacket::getHeader(void)
{
        return &m_head;
}

void* VideoPacket::getBody(void)
{
        return m_Body;
}
