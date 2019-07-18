#include <stdio.h>
#include "PThreadCond.h"
#include "BaseThread.h"
#include "TcpSocket.h"
#include "VideoSeederPacke.h"
#include "ShmFIFO.h"
#include "public.h"
#include "public.h"
//使用epoll模型接收多客户端数据，并应答
int main()
{
	int n;
	int fd = open("Realtimelogs.log", O_RDONLY ,0644);
	 Realtimelog_t * rea=new Realtimelog_t;
	 while(1)
	 {
	 	lseek(fd,0,0);
	 	if((n = read(fd,rea,sizeof(Realtimelog_t))) > 0){
	 		system("reset");
          printf("有效连接数 :%d\n",rea->Eff_conn_num);
          printf("有效接包数 :%d\n",rea->Rec_pack_num);
          printf("有效发包数 :%d\n",rea->Con_pack_num);
          printf("用户登录业务数 :%d\n",rea->User_login_service_num);
          printf("获取视频列表数 :%d\n",rea->Gets_videolist_num);
          printf("获取视频播放记录数 :%d\n",rea->Gets_videorecord_num);
          printf("上传视频播放记录数 :%d\n",rea->UpLoad_videorecord_num);
          printf("上传视频播放时间记录数 :%d\n",rea->UpLoad_videoTime_num);
      	}
	 	sleep(1);
	 }
	return 0;
}