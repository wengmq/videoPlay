#include "Socket.h"


TCPSocket::TCPSocket()
{
    m_sockfd =-1;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));  
    memset(&client_addr, 0, sizeof(struct sockaddr_in)); 
}
TCPSocket::~TCPSocket()
{
    if (isValid())
        ::close(m_sockfd);
}

bool TCPSocket::create()
{
    if (isValid())
        return false;

    if ((m_sockfd = ::socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return false;
    return true;
}

/*
   �������˲ŵ���bind���ͻ������ֹ����bind
*/
bool TCPSocket::bind(unsigned short int port, const char *ip)
{
    if (!isValid())
        return false;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (ip == NULL)
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        server_addr.sin_addr.s_addr = inet_addr(ip);
    if ( ::bind(m_sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1 )
        return false;
    return true;
}

//����Ϊ��������ʽ
bool TCPSocket::setNonBlocking(bool flag)
{
    if (!isValid())
        return false;
    int opt = fcntl(m_sockfd, F_GETFL, 0);
    if (opt == -1)
        return false;
	
    if (flag)
        opt |= O_NONBLOCK;
    else
        opt &= ~O_NONBLOCK;
    if (fcntl(m_sockfd, F_SETFL, opt) == -1)
        return false;
    return true;
}
bool TCPSocket::reuseaddr()
{
    if (!isValid())
        return false;

    int on = 1;
    if (::setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
        return false;
    return true;
}

int TCPSocket::getfd()
{
    return m_sockfd;
}

bool TCPSocket::isValid()
{
    return (m_sockfd != -1);
}

bool TCPSocket::close()
{
    //printf("TCPSocket::close  Ok!\n");
    if (!isValid())
        return false;
    ::close(m_sockfd);
    m_sockfd = -1;
    return true;
}

int TCPSocket::read(void *buf, int count)
{
    if (!isValid())
        return -1;
	
    int bytes = ::read(m_sockfd, buf, count);
    if (bytes == -1)
    {
        printf("tcp client read error\n");
	}
    return bytes;
}
int TCPSocket::write(const void *buf, int count)
{
	if (!isValid())
		return -1;
	
    int bytes = ::write(m_sockfd, buf, count);
    if ( bytes == -1 )
        printf("tcp client write error  count=%d  \n",count);
	return bytes;
}


/*
    ��֤��ȡָ�����ȵ�����,ֱ���������ݻ�����Ϊ��
*/
int TCPSocket::readn(int fd, void *buf, int count)
{
    int nLeft = count;
    int nRead = 0;
    char *pBuf = (char *)buf;

    while (nLeft > 0)
    {
        nRead = ::read(fd, pBuf, nLeft);
        if (nRead < 0)
        {            
            if (errno == EINTR)  //�����ȡ�����Ǳ��źŴ����, ��˵�������Լ�����
			    continue;                 
            else             //���������������  
                return -1;
        }        
        else if (nRead == 0)     //�Է��ر�����
            return count-nLeft;
        else  //������ȡ
        {	        
	        nLeft -= nRead;
	        pBuf += nRead;
    	}
    }
    return count;
}

/*
    ��֤����ָ�����ȵ�����,ֱ���������ݻ�����Ϊ��
*/
int TCPSocket::writen(int fd, const void *buf, int count)
{
    int nLeft = count;
    int nWritten = 0;
    char *pBuf = (char *)buf;
	
    while (nLeft > 0)
    {
        nWritten = ::write(fd, pBuf, nLeft);
        if ( nWritten < 0)
        {            
            if (errno == EINTR)  //���д������Ǳ��źŴ����, ��˵�������Լ���д�� 
                continue;            
            else                 //��������������� 
                return -1;
        }        
        else if (nWritten == 0) //��� ==0��˵����ʲôҲûд��, ���Լ���д
            continue;
        else   //����д��
    	{	       
	        nLeft -= nWritten;
	        pBuf += nWritten;
    	}
    }
    return count;
}

//send �����ݰ�����
int TCPSocket::send(Packet * pack)
{
    int writeBytes =write(pack, sizeof(Packet));
    if (writeBytes == -1)
    {
        printf("tcp client send error\n");	
	}
    return writeBytes;
}

//receive �����ݰ���ʽ����
int TCPSocket::receive(Packet * pack)
{
    int readBytes = read(pack, sizeof(Packet));
    if (readBytes == -1)
    {
        printf("tcp client receive error\n");		
	}
    else if (readBytes != sizeof(Packet))
    {
        printf("peer connect closed\n");
		close();
  	}

    return readBytes;
}


/** ------------------------ client TCP Socket -------------------**/
TCPClient::TCPClient(unsigned short int port, const char *ip)
{
    if (create() == false)
        printf("tcp client create error\n");
    if (connect(port, ip) == false)
        printf("tcp client connect error\n");
}

TCPClient::TCPClient() {}

TCPClient::TCPClient(int clientfd)
{
    m_sockfd = clientfd;
}

TCPClient::~TCPClient()
{
  
}

bool TCPClient::connect(unsigned short int port, const char *ip)
{
    if (!isValid())
        return false;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    if ( ::connect(m_sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        return false;
    return true;
}



/** ------------------ Server TCP Socket ------------------**/
TCPServer::TCPServer(unsigned short int port, const char *ip, int backlog)
{
    if (create() == false)
    {
        printf("tcp server create error\n");
		exit(0);
	}
    if (reuseaddr() == false)
    {
        printf("tcp server reuseaddr error\n");
		exit(0);
	}    
    if (bind(port, ip) == false)
    {
        printf("tcp server bind error\n");
		exit(0);
	}    
    if (listen(backlog) == false)
    {
        printf("tcp server listen error\n");
		exit(0);
	}    
	printf("tcp server create success!\n");

	
}

TCPServer::TCPServer(){};

TCPServer::~TCPServer(){}

bool TCPServer::listen(int backlog)
{
    if (!isValid())
        return false;

    if ( ::listen(m_sockfd, backlog) == -1)
        return false;
    return true;
}

int TCPServer::accept()
{
	if (!isValid())
	{
        printf("tcp server accept error\n");
		exit(0);
	}
	
	int sin_size = sizeof(struct sockaddr_in);
	m_newSocket.m_sockfd =  ::accept(this->m_sockfd, (struct sockaddr *)&client_addr, (socklen_t*)&sin_size);
	
	if (m_newSocket.m_sockfd == -1)
	{
        printf("tcp server accept error\n");
		exit(0);
	}

	printf("m_newSocket.m_sockfd = %d, IP = %s,  port = %d\n",
			m_newSocket.m_sockfd,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port)); 
    
	return m_newSocket.getfd();
	
}


