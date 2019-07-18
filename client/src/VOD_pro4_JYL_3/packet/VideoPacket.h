#ifndef VIDEOPACKET_H
#define VIDEOPACKET_H
#include "BasePacket.h"
#include "PublicPacket.h"
#include <string.h>
#include <QString>
#include <QDebug>
class VideoPacket: public BasePacket
{
public:
    VideoPacket();
    ~VideoPacket();
    bool pack();
    bool unpack();
    bool Heartbeat();
    bool Login(QString name,QString pwd);
    bool RequestType();
    bool RequestChannel();
    bool RequestVideoList(int channelId);

    packet_header_t* getHeader(void);
    void* getBody(void);

private:
packet_header_t m_head;
char m_Body[sizeof(packet_all_st) - sizeof(packet_header_t)];

};

#endif // VIDEOPACKET_H
