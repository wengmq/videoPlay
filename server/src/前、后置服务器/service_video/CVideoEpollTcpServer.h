#ifndef CVideoEpollTcpServer_H
#define CVideoEpollTcpServer_H

#include <iostream>
#include <ext/hash_map>
#include <list>
#include <iterator>
#include <algorithm>
#include "EpollTcpServer.h"
#include "TcpServer.h"
#include "EpollBase.h"
#include "VideoSeederPacke.h"
#include "ShmFIFO.h"
#include "PThreadMutex.h"
#include "CVideoSendThread.h"
#include "ImageSendThread.h"
#include "Realtimelogs.h"
#include "writeLog.h"
using namespace __gnu_cxx; // for hash_map
using namespace std;

extern Realtimelog_t reallog;
typedef struct qqclient_st
{
    int fd; //
    int delay;
    CHostAddress addr;
}QQCLIENT_T;

typedef hash_map<int,QQCLIENT_T> MP_CLIENT;
typedef list<int> LISTcli; 

class CVideoEpollTcpServer : public CEpollTcpServer
{
public:
    CVideoEpollTcpServer(CHostAddress addr,unsigned int maxEvent=10000,int timeout =3);
    ~CVideoEpollTcpServer();
    void setTimeMonit(int MaxTime);
    void Start(void);
    bool hstop;
protected:
    void OnReadData(int fd);
    void OnNewConnection();
    void OnClientClose(int fd);
    void OnTimeMonit(int Sec,int MaxTime);
    bool OnResetTime(int fd);
    void Run(int nevent);
private:
    LISTcli  lsc;
    MP_CLIENT m_mclients;
    CPacket * m_packet;
    CShmFIFO m_sendFIFO;
    CShmFIFO m_recvFIFO;
    CwriteLog * Log;

    CPThreadMutex m_mutex; 

    CVideoSendThread * m_sendThread;
    CImageSendThread * m_ImgThread;
    CRealtimelogs    * m_RealThread;
};

#endif // CVideoEpollTcpServer_H
