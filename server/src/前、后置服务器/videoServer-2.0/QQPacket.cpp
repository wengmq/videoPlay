/*************************************************************************
	> File Name: QQPacke.cpp
	> Author: eric
	> Mail: 
	> Created Time: 2017年11月24日 星期五 23时41分03秒
 ************************************************************************/

#include <iostream>
#include <string.h>
#include "QQPacket.h"

using namespace std;

CQQPacket::CQQPacket()
	:CBasePacket(sizeof(packet_all_st))
{
    memset(&m_head, 0, sizeof(m_head));
}

CQQPacket::~CQQPacket()
{
    
}

bool CQQPacket::pack()
{
   memcpy(m_data, &this->m_head, sizeof(packet_header_t));     
   memcpy(m_data+sizeof(packet_header_t), this->m_Body, sizeof(m_Body));
   return true;
}

bool CQQPacket::unpack()
{
   memcpy(&this->m_head, m_data, sizeof(packet_header_t));     
   memcpy(this->m_Body, m_data+sizeof(packet_header_t), sizeof(m_Body));    
   return true;
}




packet_header_t* CQQPacket::getHeader(void)
{
	return &m_head;
}

void* CQQPacket::getBody(void)
{
	return m_Body;
}

void CQQPacket::setFd(int fd)
{
    m_head.fd= fd;
}
int CQQPacket::getFd()
{
    return m_head.fd;
}

bool CQQPacket::Login_ret(int ret)
{
    this->dataClean();

    //填充包头
    m_head.funid = 0x01; //login
    m_head.optid = 0x00; //登录请求
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    //填充包体
    Login_ret_t *body = (Login_ret_t*)m_Body;
//    QByteArray qByteArrayName = name.toUtf8();
//    QByteArray qByteArrayPwd = pwd.toUtf8();

//    strcpy(body->usr, name);
  //  strcpy(body->psw, qByteArrayPwd.data());
    body->ret = ret;

    return this->pack();
}

bool CQQPacket::Channel_ret(int channel_id, char *channel_name, int channel_count)
{

    this->dataClean();

    //填充包头
    m_head.funid = 0x02; //login
    m_head.optid = 0x00; //请求
    m_head.usrlenth = sizeof(m_Body);
    m_head.syn = 0;

    //填充包体
    reply_channel *body = (reply_channel*)m_Body;

    body->channel_id = channel_id;

    strcpy(body->channel_name,channel_name);
    body->channel_count  = channel_count;

    return this->pack();

}
 bool CQQPacket::videolist_ret(video_list_t *list)
 {
     this->dataClean();

     //填充包头
     m_head.funid = 0x03; //login
     m_head.optid = 0x00; //请求
     m_head.usrlenth = sizeof(m_Body);
     m_head.syn = 0;

 /*
     int video_count; //视频数量
     int video_id;//视频ID
     int channel_id;//频道分类ID
     int type_ids[10];//类型分类ID,一个视频最多有10个分类
     int area_id;//地区ID
     char video_name[20];//视频名称
     int play_times;//播放次数
     char is_new; //0-旧视频 1-新视频
     char video_image[25]; //视频封面图片链接地址
     char video_address[25]; //视频网络链接地址
 */
     //填充包体
     video_list_t *body = (video_list_t*)m_Body;
    body->video_count = list->video_count;
    body->video_id = list->video_id;
    body->channel_id = list->channel_id;
    //body->type_ids = list->type_ids;
    for(int i = 0; i<10; i++)
    {
        body->type_ids[i] = list->type_ids[i];
    }

    body->area_id = list->area_id;
    strcpy(body->video_name,list->video_name);
    body->play_times = list->play_times;
    body->is_new = list->is_new;
    strcpy(body->video_image,list->video_image);
    strcpy(body->video_address,list->video_address);

     return this->pack();
 }
