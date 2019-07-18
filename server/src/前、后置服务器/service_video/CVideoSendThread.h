#ifndef CVideoSendThread_H
#define CVideoSendThread_H

#include "PThreadCond.h"
#include "BaseThread.h"
#include "TcpSocket.h"
#include "VideoSeederPacke.h"
#include "ShmFIFO.h"
#include "writeLog.h"
extern int id[70000];
//qq回包的线程
class CVideoSendThread:public CBaseThread
{
public:

    CVideoSendThread(CShmFIFO &fifo,CwriteLog * Lwr);
    ~CVideoSendThread();
	
    int run(void);
private:
    CShmFIFO &m_fifo;
    CPacket m_packet;
    CwriteLog * Log;
};

#endif // CVideoSendThread_H
