#ifndef VIDEOPACKET_H
#define VIDEOPACKET_H
#include "CBasePacket.h"
#include "public.h"
#include<string.h>
#include<QString>
#include<QDebug>
class VideoPacket: public CBasePacket
{
public:
    VideoPacket();
    ~VideoPacket();
    bool pack();
    bool unpack();
    bool Login(QString name,QString pwd);

    packet_header_t* getHeader(void);
    void* getBody(void);

private:
packet_header_t m_head;
char m_Body[sizeof(packet_all_st) - sizeof(packet_header_t)];

};

#endif // VIDEOPACKET_H
