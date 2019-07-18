#include "Realtimelogs.h"
#include "CVideoEpollTcpServer.h"
#include <stdio.h>
CRealtimelogs::CRealtimelogs()
{
 fd = open("Realtimelogs.log",O_WRONLY| O_CREAT ,0644);
}
CRealtimelogs::~CRealtimelogs()
{
}
int CRealtimelogs::run(void) 
{
    while(this->m_bRun)
    {
    	lseek(fd,0,0);
    	write(fd,&reallog,sizeof(Realtimelog_t));
    	sleep(1);
    }
     return 0;
}



