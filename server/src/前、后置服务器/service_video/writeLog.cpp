#include "writeLog.h"
#include <iconv.h>
#include <string.h>
#include <stdio.h>
CwriteLog::CwriteLog()
{
    a=true;
}
CwriteLog::~CwriteLog()
{
    close(fd);
}
void CwriteLog::writes(char * buf,int buf_len,int id,int fun,int types)
{

    if (a)
    {
        //生成日志文件(根据当前时间自动生成)
        a=false;
        char * name=new char[40];
        t = time(0);    
        local=localtime(&t);
        sprintf(name,"%04d%02d%02d.log",local->tm_year+1900,local->tm_mon + 1,local->tm_mday);
        printf("%s\n",name );
        fd = open(name,O_WRONLY| O_CREAT ,0644);
        /* code */
    }

    //要存入日志文件的参数
    char * bufs=new char[200];
   // struct tm *local;
    char * ptimes=new char[300];
    char * funanme=new char[100];
    char * idname=new char[100];
    char * typesname=new char[70];
    char * budy=new char[30];
    char * funop=new char[20];
    char type[2][10]={"发送","接收"};

    //获取当时时间
    local=localtime(&t);
    sprintf(ptimes,"时间 :%04d-%02d-%02d %02d:%02d:%02d \x0d \x0a"
        ,local->tm_year+1900,local->tm_mon + 1,local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec);

    //转化时间格式
    ptimes=UTFToGB(ptimes,sizeof(ptimes));

    //将时间写入日志文件
    write(fd,ptimes,strlen(ptimes)+1);


    switch(fun)
    {
        case 0x0001:
            strcpy(funop,"登录");
        break;
        case 0x1001:
            strcpy(funop,"获取频道");
        break;
        case 0x1003:
            strcpy(funop,"获取地区");
        break;
        case 0x1002:
            strcpy(funop,"获取分类");
        break;
        case 0x1004:
            strcpy(funop,"获取列表");
        break;
        case 0x2001:
            strcpy(funop,"点播视频");
        break;
        case 0x2002:
            strcpy(funop,"上次点播记录");
        break;
    }

    //写入 功能、类型 、用户ID
    sprintf(funanme,"功能：%s \x0d \x0a",funop);
    funanme=UTFToGB(funanme,sizeof(funanme));
    write(fd,funanme,strlen(funanme)+1);

    sprintf(typesname,"类型：%s \x0d \x0a",type[types]);
    typesname=UTFToGB(typesname,sizeof(typesname));
    write(fd,typesname,strlen(typesname)+1);

    if(id!=0)
    {
    sprintf(idname,"用户ID：%06d \x0d \x0a",id);
    idname=UTFToGB(idname,sizeof(idname));
    write(fd,idname,strlen(idname)+1);
    }

    //写入16进制数据包
    if(buf_len!=0)
    {
        strcpy(budy,"数据包(16进制): \x0d\x0a");
        budy=UTFToGB(budy,sizeof(budy));
        write(fd,budy,strlen(budy)+1);
        ByteToHexStr(buf,bufs,buf_len);
        write(fd,bufs,strlen(bufs)+1);
        write(fd," \x0d \x0a",3);
    }
    delete bufs;
    delete ptimes;
    delete funanme;
    delete idname;
    delete typesname;
}
void CwriteLog::ByteToHexStr(char *sSrc,  char *sDest, int nSrcLen )
{
    int  i;
    char * szTmp=new char[30];
    char * a=new char[nSrcLen+1];
    memcpy(a,sSrc,nSrcLen);
    for( i = 0; i < nSrcLen; i++ )
    {
        sprintf( szTmp, "%02X ", (unsigned char) a[i] );
        memcpy( &sDest[i * 3], szTmp, 3 );
    }
}
char * CwriteLog::UTFToGB(char * buf,int buf_len)
{
    iconv_t cd=iconv_open("GB2312","UTF-8");
    char*outbuf=(char*)malloc(buf_len*30);
    //bzero(outbuf,buf_len*6);
    char*in=buf;
    char*out=outbuf;
    size_t outlen=buf_len*20;
    iconv(cd,&in,(size_t*)&buf_len,&out,&outlen);
    outlen=strlen(outbuf);
    //free(outbuf);
    iconv_close(cd);
    return outbuf;
}
