#include"CQQTask.h"


int CQQTask::run()
{

    //1. unpack
    m_packet.unpack();


    switch(m_packet.getHeader()->funid)
    {
    case 0x1:
        task_login();
        printf("Login_ret: %d\n",((Login_ret_t*)m_packet_ret.getBody())->ret);
        //m_packet_ret.pack();
        m_send->write(m_packet_ret.getData());
        break;
    case 0x2:
        printf("task_GetChannel\n");
        task_GetChannel();
       // break;
    case 0x3:
        printf("task_GetvideoList\n");
        task_videolist();
        break;

    }




    return 0;
}




void CQQTask::task_login()
{

    void *pData = m_packet.getBody();

    Login_t *plogin = (Login_t*) (pData);
    printf("Back recv:%s:%s\n", plogin->usr, plogin->psw);

    int ret = login(plogin->usr,plogin->psw);
    m_packet_ret.setFd(m_packet.getFd());
    printf("m_packet_ret head fd = %d \n",m_packet_ret.getFd());
    if(ret)
    {
        printf("LoginPermit %s\n",plogin->usr);


        m_packet_ret.Login_ret(1);


    }
    else
    {
        printf("LoginRefuse %s\n",plogin->usr);

        m_packet_ret.Login_ret(666);
    }


}



void CQQTask::task_GetChannel()
{
    const char *sql ="select * from VideoClass";
    //打开数据文件
    //CSinDB::GetSinDB();

    char **dbresult;

    int rows,cols;
    sqlite3_get_table(CSinDB::GetSinDB()->Getdb(),sql,&dbresult,&rows,&cols,NULL);
    //列头下标为 0 ,数据全部保存在dbresult数组里
    for(int i=1;i<rows+1;i++)//行
    {

        //            for(int j=0;j<cols;j++)//列
        //            {
        //                printf("%s\t",dbresult[i*cols+j]);

        //            }
        //            printf("\n");


        int channel_id = atoi(dbresult[i*cols+0]);//频道ID

        char channel_name[20] = {0};
        strcpy(channel_name,dbresult[i*cols+1]);//频道名
        int channel_count = rows;//频道分类数量


        m_packet_ret.Channel_ret(channel_id,channel_name,channel_count);

        m_packet_ret.setFd(m_packet.getFd());
        printf("m_packet_ret head fd = %d \n",m_packet_ret.getFd());
        m_packet_ret.pack();
        m_send->write(m_packet_ret.getData());

    }
    sqlite3_free_table(dbresult);






}


void CQQTask::task_videolist()
{
    const char *sql ="select i.*,c.[Classtable] from VideoInfo i,VideoClass c where i.[ClassID]=c.[ClassID]";

    //打开数据文件
    //CSinDB::GetSinDB();
    char sql2[100];
    char **dbtype;
    int Type_count=0, aColumn=0;
    char **dbResult;
    video_list_t *list=new video_list_t;
    int nRow=0, nColumn=0;
    sqlite3_get_table(CSinDB::GetSinDB()->Getdb(),sql,&dbResult,&nRow,&nColumn,NULL);
    //列头下标为 0 ,数据全部保存在dbresult数组里
    for(int j=1;j<nRow+1;j++)//行
    {

        printf("VideoID:%d,ClassID:%d,AreaID:%d,Videoname:%s,playtimes:%d,Videonew:%s,VideoImg:%s,VideoAddr:%s\n",
          atoi(dbResult[j*(nColumn)]),atoi(dbResult[(j*nColumn)+1]),atoi(dbResult[(j*nColumn)+2]),dbResult[(j*nColumn)+3],
          atoi(dbResult[j*(nColumn)+4]),dbResult[(j*nColumn)+5],dbResult[(j*nColumn)+6],dbResult[(j*nColumn)+7]);


        list->video_count=nRow;
        list->video_id=atoi(dbResult[j*(nColumn)+0]);
        list->channel_id=atoi(dbResult[(j*nColumn)+1]);
        list->area_id=atoi(dbResult[(j*nColumn)+2]);
        strcpy(list->video_name,dbResult[(j*nColumn)+3]);
        list->play_times=atoi(dbResult[(j*nColumn)+4]);
        list->is_new=*dbResult[(j*nColumn)+5];
        strcpy(list->video_image,dbResult[(j*nColumn)+6]);
        strcpy(list->video_address,dbResult[(j*nColumn)+7]);

        snprintf(sql2,sizeof(sql2),"select TypeID from %s_VideoType where VideoID=%s",dbResult[(j*nColumn)+9],dbResult[j*(nColumn)]);
        sqlite3_get_table(CSinDB::GetSinDB()->Getdb(),sql2,&dbtype,&Type_count,&aColumn,NULL);
        for (int i = 1; i <= Type_count; ++i)
        {
          list->type_ids[i-1]=atoi(dbtype[i*(aColumn)]);
        }

        m_packet_ret.videolist_ret(list);

        m_packet_ret.setFd(m_packet.getFd());
        printf("m_packet_ret head fd = %d \n",m_packet_ret.getFd());
        m_packet_ret.pack();
        m_send->write(m_packet_ret.getData());

    }
    sqlite3_free_table(dbResult);


}
