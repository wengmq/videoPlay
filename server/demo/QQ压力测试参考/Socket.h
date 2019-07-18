#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#include "commen.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <fcntl.h>


/*数据包定义*/
typedef struct _Packet
{
    char  head[16];     //包头
    char  body[64];     //包体，存放数据内容
}Packet;


/*---------------基类定义----------------*/
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
    
    /**注意: TCPSocket基类并没有send/receive方法**/
    int read(void *buf, int count);
    int write(const void *buf, int count);
    int readn(int fd, void *buf, int count);
    int writen(int fd, const void *buf, int count);
    int send(Packet * pack);
    int receive(Packet * pack);

//protected:
    int m_sockfd;
    struct sockaddr_in server_addr; 
    struct sockaddr_in client_addr; //用于服务器端连接
};


/** --------------派生类TCP Client ----------------**/
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


/** --------------------派生类 TCP Server ----------------- **/
class TCPServer : public TCPSocket
{
public:
    TCPServer(unsigned short int port, const char *ip = NULL, int backlog = SOMAXCONN);
    TCPServer();
    ~TCPServer(); 

    bool listen(int backlog = SOMAXCONN);
    int accept();  //返回新建连接的描述符    
    TCPSocket m_newSocket;  //保存新的客户端连接描述符
};


#endif // SOCKET_H_INCLUDED

