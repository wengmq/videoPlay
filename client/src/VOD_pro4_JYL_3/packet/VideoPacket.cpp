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
    //����ͷ
    m_head.funid = 0x00; //����
    m_head.optid = 0x00; //����
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    return this->pack();
}

bool VideoPacket::Login(QString name,QString pwd)
{
    //����ͷ
    m_head.funid = 0x01; //login
    m_head.optid = 0x00; //��¼����
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    //������
    Login_t *body = (Login_t*)m_Body;
    QByteArray qByteArrayName = name.toUtf8();
    QByteArray qByteArrayPwd = pwd.toUtf8();

    strcpy(body->user, qByteArrayName.data());
    strcpy(body->pwd, qByteArrayPwd.data());

    return this->pack();
}

bool VideoPacket::RequestChannel()
{
    //����ͷ
    m_head.funid = 0x02; //Ƶ����������ܺ�
    m_head.optid = 0x00; //Ƶ����������
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    return this->pack();
}

bool VideoPacket::RequestType()
{
    //����ͷ
    m_head.funid = 0x04; //��Ƶ��������ܺ�
    m_head.optid = 0x00; //��Ƶ���ͷ�������
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    return this->pack();
}

bool VideoPacket::RequestVideoList(int channelId)
{
    //����ͷ
    m_head.funid = 0x03; //��Ƶ��������ܺ�
    m_head.optid = channelId; //��ƵƵ��
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
