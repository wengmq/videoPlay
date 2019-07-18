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
    int video_count; //��Ƶ����
    int video_id;//��ƵID
    int channel_id;//Ƶ������ID
    int type_ids[10];//���ͷ���ID,һ����Ƶ�����10������
    int area_id;//����ID

    char video_name[20];//��Ƶ����
    int play_times;//���Ŵ���
    char is_new; //0-����Ƶ 1-����Ƶ
    char video_image[25]; //��Ƶ����ͼƬ���ӵ�ַ
    char video_address[25]; //��Ƶ�������ӵ�ַ


    void setVideoTypeMsg(int video_count,int video_id,int channel_id,const int type_ids[]);
    void setVideoMsg(const char video_name[],int play_times,const char is_new,const char video_image[],const char video_address[]);


};

#endif // M_TOOLBUTTON_H
