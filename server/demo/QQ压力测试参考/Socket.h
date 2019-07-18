#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#include "commen.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <fcntl.h>


/*���ݰ�����*/
typedef struct _Packet
{
    char  head[16];     //��ͷ
    char  body[64];     //���壬�����������
}Packet;


/*---------------���ඨ��----------------*/
class TCPSocket
{
public:
    TCPSocket();
    ~TCPSocket();

    bool create();
    bool bind(unsigned short int port, const char *ip = NULL);
    bool reuseaddr();    
    bool setNonBlocking(bool flag);  //flag: true=SetNonBlock, false=SetBlock;
    int  getfd();
    bool isValid();    
    bool close(); 
    
    /**ע��: TCPSocket���ಢû��send/receive����**/
    int read(void *buf, int count);
    int write(const void *buf, int count);
    int readn(int fd, void *buf, int count);
    int writen(int fd, const void *buf, int count);
    int send(Packet * pack);
    int receive(Packet * pack);

//protected:
    int m_sockfd;
    struct sockaddr_in server_addr; 
    struct sockaddr_in client_addr; //���ڷ�����������
};


/** --------------������TCP Client ----------------**/
class TCPClient : public TCPSocket
{        
public:
    TCPClient(unsigned short int port, const char *ip);
    TCPClient();
    TCPClient(int clientfd);
    ~TCPClient();

    bool connect(unsigned short int port, const char *ip); 
    
private:

};


/** --------------------������ TCP Server ----------------- **/
class TCPServer : public TCPSocket
{
public:
    TCPServer(unsigned short int port, const char *ip = NULL, int backlog = SOMAXCONN);
    TCPServer();
    ~TCPServer(); 

    bool listen(int backlog = SOMAXCONN);
    int accept();  //�����½����ӵ�������    
    TCPSocket m_newSocket;  //�����µĿͻ�������������
};


#endif // SOCKET_H_INCLUDED

