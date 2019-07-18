
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "BasePacket.h"

using namespace std;

BasePacket::BasePacket(int size)
:m_size(size)
{
    m_data = new char[m_size];
}

BasePacket::BasePacket(const BasePacket &packet)
{
        m_size = packet.m_size;
        m_data = new char[packet.m_size];
        memcpy(m_data, packet.m_data, packet.m_size);
}

BasePacket::~BasePacket()
{
    delete []m_data;
}

char *BasePacket::getData()
{
    return m_data;
}

unsigned int BasePacket::getSize()
{
    return m_size;
}

BasePacket & BasePacket::operator =(const BasePacket &packet)
{
    if(m_size != packet.m_size)
    {
            delete []m_data;

            m_size = packet.m_size;
            m_data = new char[packet.m_size];
    }
    memcpy(m_data, packet.m_data, packet.m_size);
    return *this;
}

