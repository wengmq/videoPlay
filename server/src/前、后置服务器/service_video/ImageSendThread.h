#ifndef ImageSendThread_H
#define ImageSendThread_H

#include "PThreadCond.h"
#include "BaseThread.h"
#include "TcpSocket.h"
#include "VideoSeederPacke.h"
#include "CSDB.h"
//qq回包的线程
class CImageSendThread:public CBaseThread
{
public:

    CImageSendThread(int &fd,CPacket &m_packet);
    ~CImageSendThread();
	
    int run(void);
private:
	int fd;
	CSDB *db;
    CPacket m_packet;
};

#endif // CVideoSendThread_H