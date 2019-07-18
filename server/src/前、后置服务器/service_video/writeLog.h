#ifndef writeLog_H
#define writeLog_H

#include "PThreadCond.h"
#include "BaseThread.h"
#include "TcpSocket.h"
#include "VideoSeederPacke.h"
#include "ShmFIFO.h"
#include "public.h"
#include "time.h"
//qq回包的线程
class CwriteLog
{
public:

    CwriteLog();
    ~CwriteLog();

    //写入数据到日志文件
    void writes(char * buf,int buf_len,int id,int fun,int types);

    //将字节数据转化为16进制数据
    void ByteToHexStr(char *sSrc,  char *sDest, int nSrcLen );

    //数据的UTF格式转化为GB格式
    char * UTFToGB(char * buf,int buf_len);

private:
	    int fd;
	    time_t t;
	    struct tm *local;
	    bool a;
};

#endif // CwriteLog_H
