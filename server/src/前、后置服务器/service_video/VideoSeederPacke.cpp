/*************************************************************************
	> File Name: QQPacke.cpp
	> Author: eric
	> Mail: 
	> Created Time: 2017年11月24日 星期五 23时41分03秒
 ************************************************************************/

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "VideoSeederPacke.h"
#include "ShmFIFO.h"
using namespace std;



CPacket::CPacket()
:CBasePacket(sizeof(packet_all_st))
{
   memset(&m_head, 0, sizeof(m_head));
}

CPacket::~CPacket()
{
    
}

bool CPacket::pack()//打包
{
  m_size=sizeof(m_head)+this->m_head.usrlenth+sizeof(packet_tali_st);
  if(m_data !=NULL)
  {
    delete m_data;
  }
  m_data =(char *)malloc(m_size);
  memcpy(m_data, &this->m_head, sizeof(packet_header_t));     
  memcpy(m_data+sizeof(packet_header_t), this->m_Body, this->m_head.usrlenth);
  memcpy(m_data+sizeof(packet_header_t)+this->m_head.usrlenth,&this->m_tali,sizeof(packet_tali_st));
  //printf("%d %d\n",((res_login_t*)m_Body)->user_id,((res_login_t*)m_Body)->login_ret);
  return true;
}

bool CPacket::unpack()
{
  memcpy(&this->m_head, m_data, sizeof(packet_header_t));  
  this->m_Body=(char *)malloc(this->m_head.usrlenth);
  memcpy(this->m_Body, m_data+sizeof(packet_header_t), this->m_head.usrlenth);  //sizeof(m_Body)
  memcpy(&this->m_tali,m_data+sizeof(packet_header_t)+this->m_head.usrlenth,sizeof(packet_tali_st));
  return true;
}
packet_header_t* CPacket::getHeader(void)
{
  return &m_head;
}

void* CPacket::getBody(void)
{
  
  return m_Body;
}
void CPacket::detbody()
{
 if (m_Body!=NULL)
    {
      delete m_Body;
    }
}
packet_tali_st * CPacket::getTali(void)
{
  return &m_tali;
}
void CPacket::setBodysize(int size)
{
   m_Body=new char[size];
}
int CPacket::Getpacket(CTcpSocket *client)
{
    int readBytes = client->Readn((char *)getHeader(),sizeof(packet_header_t));
    setSize(sizeof(packet_header_t)+getHeader()->usrlenth+sizeof(packet_tali_st));
    if (m_Body!=NULL)
    {
      delete m_Body;
    }
    setBodysize(getHeader()->usrlenth);
    readBytes += client->Readn((char *)getBody(),getHeader()->usrlenth);
    readBytes +=client->Readn((char *)getTali(),sizeof(packet_tali_st));
    return readBytes;
}
int  CPacket::Getpacket(char *buf)
{
    memcpy(getHeader(),buf,sizeof(packet_header_t));
    setBodysize(getHeader()->usrlenth);
    setSize(sizeof(packet_header_t)+getHeader()->usrlenth+sizeof(packet_tali_st));
    memcpy(getBody(),buf+sizeof(packet_header_t),getHeader()->usrlenth);
    memcpy(getTali(),buf+sizeof(packet_header_t)+getHeader()->usrlenth,sizeof(packet_tali_st));
    return 0;
}





/*--------------------------登录包----------------------------------------
-------------------------------------------------------------------------
--------------------------------------------------------------------------
-------------------------------------------------------------------------*/
bool CPacket::Login()
{

  //填充包头
  m_head.funcId = 0x01; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(Login_t);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确

  //填充包体
  Login_t *body = new Login_t;//(Login_t*)m_Body
  
  strcpy(body->soft_ver, "11111\0");
  strcpy(body->username, "Lilu\0");
  strcpy(body->psw, "123456\0");
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  //打包，封包
  return this->pack();
}
bool CPacket::Login_res(int id,int ret)
{
   //填充包头
  m_head.funcId = 0x0001; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(res_login_st);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //m_head.fd=0;
  //填充包体
  res_login_t *body =  new res_login_t;
  body->user_id=id;
  body->login_ret=ret;
  if (m_Body!=NULL)
  {
    /* code */
    delete m_Body;
  }
  
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}

bool CPacket::Login_call(CSDB *db)
{
  char  sql[150]; 
  char **dbResult;  
  int nRow, nColumn;
  Login_t *plogin = (Login_t*)(m_Body);//转化为登录包
  if (plogin==NULL)
  {
    Login_res(0,0);
    return false;
  }
  if (strcmp(plogin->username,"")==0 && plogin->psw==NULL)
  {
    Login_res(0,0);
    return false;
  }
  printf("Back recv:%s:%s\n",plogin->username, plogin->psw);
  snprintf(sql,sizeof(sql),"select count(*),UserID from UserInfo where Username='%s' and Passwd=%s ",plogin->username,plogin->psw);
  db->Get_table(sql, &dbResult, &nRow,&nColumn);
  if(dbResult !=NULL)
  {
    if(atoi(dbResult[nColumn])>0)
    {
      printf("登录成功\n");
      //write("登录成功",5);
      Login_res(atoi(dbResult[nColumn+1]),1);
    }
    else
    {
      Login_res(0,0);
    }
  }
  db->Free_table(dbResult);
  return this->pack();
}
/*--------------------------获取频道----------------------------------------
-------------------------------------------------------------------------
--------------------------------------------------------------------------
-------------------------------------------------------------------------*/
bool CPacket::GetClass()
{

  //填充包头
  m_head.funcId = 0x1001; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = 0;// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  m_tali.pack_tail=0x05;
  //打包，封包
  return this->pack();
}
bool CPacket::Class_res(int count,int id,char * Name)
{
   //填充包头
  m_head.funcId = 0x1001; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(VideoChannel);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //m_head.fd=0;
  //填充包体
  VideoChannel *body =  new VideoChannel;
  body->classes_count=count;
  body->classes_id=id;
  strcpy(body->classes_name,Name);
    if (m_Body!=NULL)
  {
    /* code */
    delete m_Body;
  }
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::Class_call(CSDB *db,void *m_send)
{
  char **dbResult;  
  int nRow=0, nColumn=0;
  db->Get_table((char *)"select ClassID,Classname from VideoClass", &dbResult, &nRow,&nColumn);
  printf("nRow:%d\n", nRow);
  for (int j = 1; j <= nRow; ++j)
  {
      printf("classes_id:%s,classes_name:%s\n",dbResult[j*(nColumn)],dbResult[(j*nColumn)+1]);
      Class_res((nRow),atoi(dbResult[j*(nColumn)]),dbResult[(j*nColumn)+1]);
      ((CShmFIFO*)m_send)->write(getData());
      sleep(0.01);
  }
  db->Free_table(dbResult);

  //return this->pack();
  return true;
}
/*--------------------------获取记录----------------------------------------
-------------------------------------------------------------------------
--------------------------------------------------------------------------
-------------------------------------------------------------------------*/
bool CPacket::Getrecord(int id)
{

  //填充包头
  m_head.funcId = 0x1005; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(History_t);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  m_tali.pack_tail=0x05;
  History_t * body=new History_t;
  body->user_id=id;
  if (m_Body !=NULL)
  {
    delete m_Body;
  }
  this->m_Body=(char *)body;
  //打包，封包
  return this->pack();
}
bool CPacket::record_res(int id,int read_time)
{
   //填充包头
  m_head.funcId = 0x1005; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(PlayHistory_t);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //m_head.fd=0;
  //填充包体
  PlayHistory_t *body =  new PlayHistory_t;
  body->video_id=id;
  body->video_seek=read_time;
  if (m_Body !=NULL)
  {
    delete m_Body;
    /* code */
  }
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::record_call(CSDB *db,void *m_send)
{
  char sql[100];
  char **dbResult;  
  int nRow=0, nColumn=0;
  History_t * plogin =(History_t *) (getBody());
  if (plogin->user_id==0)
  {
    record_res(0,0);
    ((CShmFIFO*)m_send)->write(getData());
    return false;
  }
  sprintf(sql,"select VideoID,PlayTime from Userecord where UserID='%d'",plogin->user_id);
  db->Get_table(sql, &dbResult, &nRow,&nColumn);
  printf("nRow:%d\n", nRow);
  for (int j = 1; j <= nRow; ++j)
  {
      printf("classes_id:%s,classes_name:%s\n",dbResult[j*(nColumn)],dbResult[(j*nColumn)+1]);
      record_res(atoi(dbResult[j*(nColumn)]),atoi(dbResult[(j*nColumn)+1]));
      ((CShmFIFO*)m_send)->write(getData());
      sleep(0.01);
  }
  db->Free_table(dbResult);

  //return this->pack();
  return true;
}
/*--------------------------获取频道地区----------------------------------------
-------------------------------------------------------------------------
--------------------------------------------------------------------------
-------------------------------------------------------------------------*/
bool CPacket::GetArea()
{

  //填充包头
  m_head.funcId = 0x1003; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = 0;// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  m_tali.pack_tail=0x05;
  //打包，封包
  return this->pack();
}
bool CPacket::Area_res(int count,int claid,int id,char * Name)
{
   //填充包头
  m_head.funcId = 0x1003; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(VideoArea);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //m_head.fd=0;
  //填充包体
  VideoArea *body =  new VideoArea;
  body->area_count=count;
  body->classes_id=claid;
  body->area_id=id;
  strcpy(body->area_name,Name);
  if (m_Body!=NULL)
  {
    delete m_Body;
  }
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::Area_call(CSDB *db,void *m_send)
{
  char **dbcla;  
  int cla_count=0, Column=0;
  char sql[100];
  char **dbArea;  
  int area_count=0, aColumn=0;
  db->Get_table((char *)"select ClassID,Classtable from VideoClass", &dbcla, &cla_count,&Column);
  printf("nRow:%d\n", cla_count);
  for (int j = 1; j <= cla_count; ++j)
  {
      printf("ClassID:%s,Classtable:%s\n",dbcla[j*(Column)],dbcla[(j*Column)+1]);
      snprintf(sql,sizeof(sql),"select AreaID,Areaname from %s_Area",dbcla[(j*Column)+1]);
      db->Get_table(sql, &dbArea, &area_count,&aColumn);
      for (int i = 1; i <= area_count; ++i)
      {
        printf("AreaID:%s,Areaname:%s\n",dbArea[i*(aColumn)],dbArea[(i*aColumn)+1]);
        Area_res(area_count,atoi(dbcla[j*(Column)]),atoi(dbArea[i*(aColumn)]),dbArea[(i*aColumn)+1]);
        ((CShmFIFO*)m_send)->write(getData());
        sleep(0.01);
      }
      db->Free_table(dbArea);
  }
  db->Free_table(dbcla);
  //return this->pack();
  return true;
}

/*--------------------------获取频道分类----------------------------------------
-------------------------------------------------------------------------
--------------------------------------------------------------------------
-------------------------------------------------------------------------*/
bool CPacket::GetType()
{

  //填充包头
  m_head.funcId = 0x1002; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = 0;// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  m_tali.pack_tail=0x05;
  //打包，封包
  return this->pack();
}
bool CPacket::Type_res(int count,int claid,int id,char * Name)
{
   //填充包头
  m_head.funcId = 0x1002; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(VideoType);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //m_head.fd=0;
  //填充包体
  VideoType *body =  new VideoType;
  body->type_count=count;
  body->classes_id=claid;
  body->type_id=id;
  strcpy(body->type_name,Name);
  if (m_Body!=NULL)
  {
    delete m_Body;
  }
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::Type_call(CSDB *db,void *m_send)
{
  char **dbcla;  
  int cla_count=0, Column=0;
  char sql[100];
  char **dbtype;  
  int Type_count=0, aColumn=0;
  db->Get_table((char *)"select ClassID,Classtable from VideoClass", &dbcla, &cla_count,&Column);
  printf("nRow:%d\n", cla_count);
  for (int j = 1; j <= cla_count; ++j)
  {
      printf("ClassID:%s,Classtable:%s\n",dbcla[j*(Column)],dbcla[(j*Column)+1]);
      snprintf(sql,sizeof(sql),"select TypeID,Typename from %s_Type",dbcla[(j*Column)+1]);
      db->Get_table(sql, &dbtype, &Type_count,&aColumn);

      for (int i = 1; i <= Type_count; ++i)
      {
        printf("AreaID:%s,Areaname:%s\n",dbtype[i*(aColumn)],dbtype[(i*aColumn)+1]);
        Type_res(Type_count,atoi(dbcla[j*(Column)]),atoi(dbtype[i*(aColumn)]),dbtype[(i*aColumn)+1]);
        ((CShmFIFO*)m_send)->write(getData());
        sleep(0.01);
      }
      db->Free_table(dbtype);
  }
  db->Free_table(dbcla);
  //return this->pack();
  return true;
}

/*--------------------------获取频道列表----------------------------------------
-------------------------------------------------------------------------
--------------------------------------------------------------------------
-------------------------------------------------------------------------*/
bool CPacket::GetvideoList()
{

  //填充包头
  m_head.funcId = 0x1004; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = 0;// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  m_tali.pack_tail=0x05;
  //打包，封包
  return this->pack();
}
bool CPacket::videoList_res(VideoList *list)
{
   //填充包头
  m_head.funcId = 0x1004; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(VideoList);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //m_head.fd=0;
  //填充包体
  // if (m_Body!=NULL)
  // {
  //   delete m_Body;
  // }
  this->m_Body=(char *)list;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::videoList_call(CSDB *db,void *m_send)
{
  char sql[100];
  char **dbtype;  
  int Type_count=0, aColumn=0;
  char **dbResult;  
  int nRow=0, nColumn=0;
  VideoList *list=new VideoList;
  db->Get_table((char *)"select i.*,c.[Classtable] from VideoInfo i,VideoClass c where i.[ClassID]=c.[ClassID]", &dbResult,&nRow,&nColumn);
  printf("nRow:%d\n", nRow);
  for (int j = 1; j <= nRow; ++j)
  {
      printf("VideoID:%d,ClassID:%d,AreaID:%d,Videoname:%s,playtimes:%d,Videonew:%s,VideoImg:%s,VideoAddr:%s\n",
        atoi(dbResult[j*(nColumn)]),atoi(dbResult[(j*nColumn)+1]),atoi(dbResult[(j*nColumn)+2]),dbResult[(j*nColumn)+3],
        atoi(dbResult[j*(nColumn)+4]),dbResult[(j*nColumn)+5],dbResult[(j*nColumn)+6],dbResult[(j*nColumn)+7]);
      list->video_count=nRow;
      list->video_id=atoi(dbResult[j*(nColumn)]);
      list->classes_id=atoi(dbResult[(j*nColumn)+1]);
      list->area_id=atoi(dbResult[(j*nColumn)+2]);
      strcpy(list->video_name,dbResult[(j*nColumn)+3]);
      list->play_times=atoi(dbResult[(j*nColumn)+4]);
      list->is_new=*dbResult[(j*nColumn)+5];
      strcpy(list->video_image,dbResult[(j*nColumn)+6]);
      strcpy(list->video_address,dbResult[(j*nColumn)+7]);
      snprintf(sql,sizeof(sql),"select TypeID from %s_VideoType where VideoID=%s",dbResult[(j*nColumn)+9],dbResult[j*(nColumn)]);
      db->Get_table(sql, &dbtype, &Type_count,&aColumn);
      for (int i = 1; i <= Type_count; ++i)
      {
        list->type_ids[i-1]=atoi(dbtype[i*(aColumn)]);
      }
      videoList_res(list);
      ((CShmFIFO*)m_send)->write(getData());
      sleep(0.01);
  }
  db->Free_table(dbResult);

  //return this->pack();
  return true;
}

/*--------------------------获取视频图片----------------------------------------
-------------------------------------------------------------------------
--------------------------------------------------------------------------
-------------------------------------------------------------------------*/
bool CPacket::GetvideoImg()
{

  //填充包头
  m_head.funcId = 0x1011; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = 0;// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  m_tali.pack_tail=0x05;
  //打包，封包
  return this->pack();
}
bool CPacket::videoImg_res(Image_t * img)
{
   //填充包头
  m_head.funcId = 0x1011; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(Image_t);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  this->m_Body=(char *)img;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
/*----------------------------获取流水号---------------------------------------*/
bool CPacket::getSer_num(int fun)
{
  //填充包头
  m_head.funcId = fun; //login
  m_head.optid = 0x01; //登录请求
  m_head.usrlenth = 0;// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //填充包体
  if (m_Body!=NULL)
  {
    delete m_Body;
  }
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::Ser_num(int fun)
{
  char a[23]="\0";
  struct tm *local;
  time_t t;
   //填充包头
  m_head.funcId = fun; //login
  m_head.optid = 0x01; //登录请求
  m_head.usrlenth = 23;// 包体的长度
  m_head.syn = 0;// 判断包头是否正确 
  t = t + 8*3600;
  time(&t);
  local=localtime(&t);
  sprintf(a,"%04d%02d%02d%02d%02d%02d%04X%05d"
    ,local->tm_year+1900,local->tm_mon + 1,local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec,fun,rand()%99999);
  printf("%s\n", a);
  //填充包体
  if (m_Body!=NULL)
  {
    delete m_Body;
  }
  this->m_Body=a;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
//客户端上传视频点播功能
bool CPacket::UploadVideoPlay(int i_user_id, int i_video_id, char *p_Ser_num)
{
     //填充包头
  m_head.funcId = 0x2001; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(VideoPlay_t);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //m_head.fd=0;
  //填充包体
  VideoPlay_t *body =  new VideoPlay_t;
  body->user_id=i_user_id;
  body->video_id=i_video_id;
  strcpy(body->update_flowid,p_Ser_num);
  printf("user_id:%i video_id:%i update_flowid:%s\n", body->user_id, body->video_id, body->update_flowid);
  if (m_Body!=NULL)
  {
    delete m_Body;
  }
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::UploadVideoPlay_res(int i_result)
{
     //填充包头
  m_head.funcId = 0x2001; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(UpLoad);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //填充包体
  UpLoad *body =  new UpLoad;
  body->results=i_result;
  strcpy(body->update_flowid, ((VideoPlay *)(this->m_Body))->update_flowid);
  //printf("result:%i update_flowid:%s\n", body->results, body->update_flowid);
  if (m_Body!=NULL)
  {
    delete m_Body;
  }
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::UploadVideoPlay_call(CSDB *db)
{
  int ret;
  char sql[150]="\0";
  char time[15]="\0";
  char **dbResult;  
  int nRow=0, nColumn=0;
  VideoPlay_t * videop =(VideoPlay_t *) (getBody());
  memcpy(time,videop->update_flowid,12);  
  //printf("%s\n",time);
  sprintf(sql,"select count(*) from Userecord where VideoID='%d' and UserID='%d';",videop->video_id,videop->user_id);
  ret=db->Get_table(sql, &dbResult, &nRow,&nColumn);
  if(atoi(dbResult[nColumn])>0)
        sprintf(sql,"update  Userecord set lastrecord='%s' where VideoID='%d' and UserID='%d';",time,videop->video_id,videop->user_id);
  else
        sprintf(sql,"insert into Userecord values(null,%d,%d,0,'%s');",videop->user_id,videop->video_id,time);
  ret=db->Get_table(sql, &dbResult, &nRow,&nColumn);
  sprintf(sql,"insert into VideoRecord values(null,%d,'%s',%d);",videop->video_id,time,videop->user_id);
  ret+=db->Get_table(sql, &dbResult, &nRow,&nColumn);
  sprintf(sql,"update  VideoInfo set playtimes=playtimes+1 where VideoID=%d;",videop->video_id);
  ret+=db->Get_table(sql, &dbResult, &nRow,&nColumn);
  printf("nRow:%d\n", nRow);
  UploadVideoPlay_res(ret);
  db->Free_table(dbResult);
  return true;
}
bool CPacket::UploadVideoRecord(int i_user_id, int i_video_id, int i_video_seek, char *p_Ser_num)//客户端上传视频点播时长功能
{
       //填充包头
  m_head.funcId = 0x2002; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(VideoRecord);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //m_head.fd=0;
  //填充包体
  VideoRecord *body =  new VideoRecord;
  body->user_id=i_user_id;
  body->video_id=i_video_id;
  body->video_seek=i_video_seek;
  strcpy(body->update_flowid,p_Ser_num);
  printf("user_id:%i video_id:%i video_seek:%i update_flowid:%s\n", body->user_id, body->video_id, body->video_seek, body->update_flowid);
  if (m_Body!=NULL)
  {
    delete m_Body;
  }
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::UploadVideoRecord_res(int i_result)
{
     //填充包头
  m_head.funcId = 0x2002; //login
  m_head.optid = 0x00; //登录请求
  m_head.usrlenth = sizeof(UpLoad);// 包体的长度
  m_head.syn = 0;// 判断包头是否正确
  //填充包体
  UpLoad *body =  new UpLoad;
  body->results=i_result;
  strcpy(body->update_flowid, ((VideoRecord *)(this->m_Body))->update_flowid);
  //printf("result:%i update_flowid:%s\n", body->results, body->update_flowid);
  if (m_Body!=NULL)
  {
    delete m_Body;
  }
  this->m_Body=(char *)body;
  m_tali.pack_tail=0x05;
  // //打包，封包
   return this->pack();
}
bool CPacket::UploadVideoRecord_call(CSDB *db)
{
  int ret;
  char sql[150]="\0";
  char time[15]="\0";
  char **dbResult;  
  int nRow=0, nColumn=0;
  VideoRecord * videop =(VideoRecord *) (getBody());
  memcpy(time,videop->update_flowid,12);  
  //printf("%s\n",time);
  sprintf(sql,"update  Userecord set PlayTime=%d where VideoID=%d and UserID=%d;",videop->video_seek,videop->video_id,videop->user_id);
  ret=db->Get_table(sql, &dbResult, &nRow,&nColumn);
  printf("nRow:%d\n", nRow);
  UploadVideoRecord_res(ret);
  db->Free_table(dbResult);
  return true;
}
