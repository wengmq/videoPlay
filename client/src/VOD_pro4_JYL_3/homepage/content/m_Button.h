#ifndef M_BUTTON_H
#define M_BUTTON_H

#include <QPushButton>
class m_Button:public QPushButton
{
    Q_OBJECT
public:
    explicit  m_Button(QWidget *parent = 0);
    ~m_Button(){}

    int channel_count;//Ƶ����������
    int channel_id;//Ƶ��ID
    char channel_name[20];//Ƶ����

    void setChannelMsg(int count,int id,const char *name);
};

#endif // M_BUTTON_H
