#ifndef ImageGet_H
#define ImageGet_H

#include "PThreadCond.h"
#include "BaseThread.h"
#include "TcpSocket.h"
#include "VideoSeederPacke.h"
#include "ShmFIFO.h"
#include "public.h"
//qq回包的线程
class CImageGet:public CBaseThread
{
public:

    CImageGet(CShmFIFO &fifo);
    ~CImageGet();
	
    int run(void);
private:
    CShmFIFO &m_fifo;
};

#endif // CImageGet_H
