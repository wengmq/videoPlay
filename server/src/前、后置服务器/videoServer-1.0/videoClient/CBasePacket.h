#ifndef CBASEPACKET_H
#define CBASEPACKET_H

class CBasePacket
{
public:
    CBasePacket(int size);
    CBasePacket(const CBasePacket &packet);
    virtual ~CBasePacket();
    virtual bool pack()=0;
    virtual bool unpack()=0;
    CBasePacket & operator = (const CBasePacket &packet);
    char *getData(); //��ȡ������
    unsigned int getSize(); //��ȡ������

protected:
    char    *m_data;
    unsigned m_size;
};


#endif // CBASEPACKET_H
