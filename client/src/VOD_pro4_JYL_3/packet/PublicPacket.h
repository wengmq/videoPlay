#ifndef PUBLICPACKET_H
#define PUBLICPACKET_H

//包头
typedef struct packet_header_st
{
        char srcAddr[6]; //预留
        char dstAddr[6]; //预留
        int funid; // 功能号
        int optid; // 操作码：请求和应答
        int usrlenth;// 包体的长度
        int syn; // 判断包头是否正确
        int fd; //用于前后端消息通信

}packet_header_t;


//整个包
typedef struct  packet_all_st
{
        packet_header_t head;
        char data[1024-sizeof(packet_header_t)]; // ??
        //unsigned len; //要发送的数据有效长度

}packet_all_st;

typedef struct pack_back
{
        int syn;
}Pack_Back;

//登陆包0x01
typedef struct login
{
        char user[10];//用户名
        char pwd[10];//密码
}Login_t;

//登陆应答包
typedef struct login_ret
{
        //char usr[10];//
        int ret;//登陆结果 0错误 1正确
}login_ret_t;


//0x02
//频道分类应答包
typedef struct reply_channel
{
        int channel_count;//频道分类数量
        int channel_id;//频道ID
        char channel_name[20];//频道名
}reply_channel_t;

//0x03
//视频列表应答包
typedef struct video_list
{
        int video_count; //视频数量
        int video_id;//视频ID
        int channel_id;//频道分类ID
        int type_ids[10];//类型分类ID,一个视频最多有10个分类
        int area_id;//地区ID
        char video_name[20];//视频名称
        int  play_times;//播放次数
        char is_new; //0-旧视频 1-新视频
        char video_image[25]; //视频封面图片链接地址
        char video_address[25]; //视频网络链接地址
}video_list_t;



//
//视频类型分类应答包
typedef struct reply_type
{
        int type_count;//视频类型分类数量
        int channel_id;//视频频道ID
        int type_id;//视频类型ID
        char type_name[10];//视频类型名
}reply_type_t;

//0x04
//地区分类应答包
typedef struct
{
        int area_count;//视频地区分类数量
        int channel_id;//视频频道分类ID
        int area_id;//视频地区分类ID
        char area_name[10];//视频地区分类名称
}reply_area;

//0x05
//视频列表
typedef struct
{
        char VideoName[20];//视频名
}reply_list;




//0x06
//视频点播功能
typedef struct
{
    int state;
    char updata_flowid[32];//
}reply_play;



//
typedef struct Log_st
{
    int reccount;//接收数据包
    int sendcount;//发送数据包
    int connectcount;//有效连接数
    int logincount;//用户登录业务数
    int getvlistcount;//获取视频列表数
    int getvrecordcount;//获取用户播放记录业务数
    int uploadrcount;//上传视频点播记录业务数
    int uploadtimecount;//上传视频点播时长记录业务数
}Log_t;



#endif // PUBLICPACKET_H
