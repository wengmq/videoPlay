#ifndef M_TOOLBUTTON_H
#define M_TOOLBUTTON_H


#include <QToolButton>
#include "../../videoPlay/ffvideoplayer.h"
class m_ToolButton :public QToolButton
{
    Q_OBJECT
public:
   explicit m_ToolButton(QWidget *parent=0);
    ~m_ToolButton(){}

 public slots:
    void videoPlaySlot();

public:
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


    void setVideoTypeMsg(int video_count,int video_id,int channel_id,const int type_ids[]);
    void setVideoMsg(const char video_name[],int play_times,const char is_new,const char video_image[],const char video_address[]);


};

#endif // M_TOOLBUTTON_H
