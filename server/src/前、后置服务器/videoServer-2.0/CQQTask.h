#ifndef _CQQTASK_H
#define _CQQTASK_H
#include "PThreadPool.h"
#include "PThreadBase.h"
#include "PThreadCond.h"
#include "ShmFIFO.h"
#include "QQPacket.h"
#include "CSinDB.h"
#include"BackServerFunction.h"

class CQQTask: public CTask
{
public:
        CQQTask(CShmFIFO &send, CQQPacket& packet)
                :m_send(&send), m_packet(packet)
        {
        }

        CQQTask(){};

        int run();
        void task_login();
        void task_GetChannel();
        void task_videolist();

private:
        CShmFIFO *m_send;
        CQQPacket m_packet;
        CQQPacket m_packet_ret;
};


#endif
