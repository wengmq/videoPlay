#ifndef BASEPACKET_H
#define BASEPACKET_H


#include <iostream>

class BasePacket
{
public:
    BasePacket(int size);
    BasePacket(const BasePacket &packet);
    virtual ~BasePacket();
    virtual bool pack()=0;  //���
    virtual bool unpack()=0;//���
    BasePacket & operator = (const BasePacket &packet);
    char *getData();        //��ȡ������
    unsigned int getSize(); //��ȡ������

protected:
    char    *m_data;
    unsigned m_size;
};

#endif // BASEPACKET_H

