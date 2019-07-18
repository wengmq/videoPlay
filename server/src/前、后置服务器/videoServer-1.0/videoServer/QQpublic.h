#ifndef __QQ_PUBLIC_H
#define __QQ_PUBLIC_H

#include <sys/types.h>
#include <sys/ipc.h>

#define KEY_FIFO_SEND   ftok(".", 1)
#define KEY_FIFO_RECV   ftok(".", 2)



typedef struct packet_header_st
{
	char srcAddr[6]; //预留
	char dstAddr[6]; //预留
	int funid; // 功能号
	int optid; // 操作码：请求和应答
	int usrlenth;// 包体的长度
	int syn; // 判断包头是否正确
	int fd; //用于前后端消息通信

}packet_header_t;


typedef struct  packet_all_st
{
	packet_header_t head;
	char data[1024-sizeof(packet_header_t)]; // ??
	//unsigned len; //要发送的数据有效长度

}packet_all_st;

typedef struct pack_back
{
	int syn;
}Pack_Back;

//登录包
typedef struct login
{
	char usr[10]; //QQ号？？
	char psw[10];
}Login_t;

//登录应答包
typedef struct login_ret
{
        //char usr[10]; //QQ号？？
        int ret; //正确为 1，错误为0
}Login_ret_t;

//登录应答包
typedef struct res_login_st
{
	int id; //在线的顺序
}res_login_t;

typedef struct message
{
	char usr[10];
	char mess[100];
}MESSAGE;


#endif /* __QQ_PUBLIC_H */
