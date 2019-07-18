#ifndef __QQ_PUBLIC_H
#define __QQ_PUBLIC_H

#include <sys/types.h>
#include <sys/ipc.h>

#define KEY_FIFO_SEND   ftok(".", 1)
#define KEY_FIFO_RECV   ftok(".", 2)



typedef struct packet_header_st
{
	char srcAddr[6]; //Ԥ��
	char dstAddr[6]; //Ԥ��
	int funid; // ���ܺ�
	int optid; // �����룺�����Ӧ��
	int usrlenth;// ����ĳ���
	int syn; // �жϰ�ͷ�Ƿ���ȷ
	int fd; //����ǰ�����Ϣͨ��

}packet_header_t;


typedef struct  packet_all_st
{
	packet_header_t head;
	char data[1024-sizeof(packet_header_t)]; // ??
	//unsigned len; //Ҫ���͵�������Ч����

}packet_all_st;

typedef struct pack_back
{
	int syn;
}Pack_Back;

//��¼��
typedef struct login
{
	char usr[10]; //QQ�ţ���
	char psw[10];
}Login_t;

//��¼Ӧ���
typedef struct login_ret
{
        //char usr[10]; //QQ�ţ���
        int ret; //��ȷΪ 1������Ϊ0
}Login_ret_t;

//��¼Ӧ���
typedef struct res_login_st
{
	int id; //���ߵ�˳��
}res_login_t;

typedef struct message
{
	char usr[10];
	char mess[100];
}MESSAGE;


#endif /* __QQ_PUBLIC_H */
