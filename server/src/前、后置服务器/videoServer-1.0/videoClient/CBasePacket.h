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
    char *getData(); //获取的数据
    unsigned int getSize(); //获取包长度

protected:
    char    *m_data;
    unsigned m_size;
};


#endif // CBASEPACKET_H
