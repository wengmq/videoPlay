#ifndef BASEPACKET_H
#define BASEPACKET_H


#include <iostream>

class BasePacket
{
public:
    BasePacket(int size);
    BasePacket(const BasePacket &packet);
    virtual ~BasePacket();
    virtual bool pack()=0;  //封包
    virtual bool unpack()=0;//解包
    BasePacket & operator = (const BasePacket &packet);
    char *getData();        //获取的数据
    unsigned int getSize(); //获取包长度

protected:
    char    *m_data;
    unsigned m_size;
};

#endif // BASEPACKET_H

