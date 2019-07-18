#include "TcpSocket.h"

CTcpSocket::CTcpSocket(void)
{
    Create();
}

CTcpSocket::~CTcpSocket(void)
{
}

CTcpSocket::CTcpSocket(int fd)
{
//	printf("CTcpSocket(int fd) = %d\n",fd );
    CBaseSocket::SetSocket(fd);
}
void CTcpSocket::setID(int &id)
{
    user_id=id;
}
int CTcpSocket::getID()
{
    return user_id;
}
CTcpSocket::CTcpSocket(const CTcpSocket &other)
{
    CBaseSocket::SetSocket(other.GetSocket());
    SetRemoteAddr(other.GetRemoteAddr());
}

CTcpSocket & CTcpSocket::operator =(const CTcpSocket &other)
{
    CBaseSocket::SetSocket(other.GetSocket());
    SetRemoteAddr(other.GetRemoteAddr());
    return *this;
}

CHostAddress CTcpSocket::GetRemoteAddr() const
{
    CHostAddress addr;
    memset(&addr, 0, sizeof(addr));
    //printf("m_fd:%d\n",m_fd);
    if(getpeername(m_fd, addr.Address(), addr.LengthPtr()) != 0)//用于获取与m_fd套接字关联的外地协议地址和端口
    {
        perror("getpeername error");
    }
    return addr;
}

void CTcpSocket::Create()
{
    CBaseSocket::Create(AF_INET,SOCK_STREAM,0);
}

void CTcpSocket::SetRemoteAddr(const CHostAddress remote_addr)
{
    m_remote_addr = remote_addr;//对方的连接地址
}

bool CTcpSocket::Connect(CHostAddress addr)
{
    int ret = connect(m_fd, addr.Address(), addr.Length());
    if(ret == 0)
        SetRemoteAddr(addr);
    else
        perror("Connect to server error");
    return ret == 0 ? true:false;
}

int CTcpSocket::Read(char *buf, const int buf_len)
{
    return m_stream.Read(buf,buf_len);
}

int CTcpSocket::Readn(char *buf, const int buf_len)
{
    return m_stream.Readn(buf,buf_len);
}

int CTcpSocket::Read(char *buf, const int buf_len,struct  timeval *tv)
{
    return m_stream.Read(buf,buf_len,tv);
}

int CTcpSocket::Write(char *buf, const int buf_len)
{
    return m_stream.Write(buf,buf_len);
}

int CTcpSocket::Writen(char *buf, const int buf_len)
{
    return m_stream.Writen(buf,buf_len);
}

int CTcpSocket::Write(char *buf, const int buf_len, struct timeval *tv)
{
     return m_stream.Write(buf,buf_len,tv);
}
