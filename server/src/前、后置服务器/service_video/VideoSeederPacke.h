
#ifndef _VIDEOSEEDERPACKE_H
#define _VIDEOSEEDERPACKE_H
#include "Packet.h"
#include "public.h"//定义包头packet_header_t
#include "TcpSocket.h"
#include "CSDB.h"

class CPacket: public CBasePacket
{
public:
    CPacket();
    ~CPacket();
   bool pack();
   bool unpack();
   bool Login();
   bool Login_res(int id,int ret);
   
   packet_header_t * getHeader(void);
   void* getBody(void);
   packet_tali_st * getTali(void);
   void setBodysize(int size);
   void detbody();
   int Getpacket(CTcpSocket *client);
   int Getpacket(char *buf);
   bool Login_call(CSDB *db);
   bool GetClass();
   bool Class_res(int count,int id,char * Name);
   bool Class_call(CSDB *db,void *m_send);

   bool Getrecord(int id);
   bool record_res(int id,int read_time);
   bool record_call(CSDB *db,void *m_send);

   bool GetArea();
   bool Area_res(int count,int claid,int id,char * Name);
   bool Area_call(CSDB *db,void *m_send);

   bool GetType();
   bool Type_res(int count,int claid,int id,char * Name);
   bool Type_call(CSDB *db,void *m_send);

   bool GetvideoList();
   bool videoList_res(VideoList *list);
   bool videoList_call(CSDB *db,void *m_send);
   
   bool GetvideoImg();
   bool videoImg_res(Image_t * img);

   bool getSer_num(int fun);
   bool Ser_num(int fun);
   
   bool UploadVideoPlay(int i_user_id, int i_video_id, char *p_Ser_num);//客户端上传视频点播功能
   bool UploadVideoPlay_res(int i_result);
   bool UploadVideoPlay_call(CSDB *db);

   bool UploadVideoRecord(int i_user_id, int i_video_id, int i_video_seek, char *p_Ser_num);//客户端上传视频点播时长功能
   bool UploadVideoRecord_res(int i_result);
   bool UploadVideoRecord_call(CSDB *db);
private:
    packet_header_t m_head;
    char * m_Body;
    packet_tali_st  m_tali;
};

#endif
