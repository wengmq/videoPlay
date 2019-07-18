#ifndef Realtimelogs_H
#define Realtimelogs_H

#include "PThreadCond.h"
#include "BaseThread.h"
#include "TcpSocket.h"
#include "VideoSeederPacke.h"
#include "CSDB.h"
//qq回包的线程
class CRealtimelogs:public CBaseThread
{
public:

    CRealtimelogs();
    ~CRealtimelogs();
	
    int run(void);
private:
	int fd;
};

#endif // CVideoSendThread_H