#ifndef PUBLICPACKET_H
#define PUBLICPACKET_H

//��ͷ
typedef struct packet_header_st
{
        char srcAddr[6]; //Ԥ��
        char dstAddr[6]; //Ԥ��
        int funid; // ���ܺ�
        int optid; // �����룺�����Ӧ��
        int usrlenth;// ����ĳ���
        int syn; // �жϰ�ͷ�Ƿ���ȷ
        int fd; //����ǰ�����Ϣͨ��

}packet_header_t;


//������
typedef struct  packet_all_st
{
        packet_header_t head;
        char data[1024-sizeof(packet_header_t)]; // ??
        //unsigned len; //Ҫ���͵�������Ч����

}packet_all_st;

typedef struct pack_back
{
        int syn;
}Pack_Back;

//��½��0x01
typedef struct login
{
        char user[10];//�û���
        char pwd[10];//����
}Login_t;

//��½Ӧ���
typedef struct login_ret
{
        //char usr[10];//
        int ret;//��½��� 0���� 1��ȷ
}login_ret_t;


//0x02
//Ƶ������Ӧ���
typedef struct reply_channel
{
        int channel_count;//Ƶ����������
        int channel_id;//Ƶ��ID
        char channel_name[20];//Ƶ����
}reply_channel_t;

//0x03
//��Ƶ�б�Ӧ���
typedef struct video_list
{
        int video_count; //��Ƶ����
        int video_id;//��ƵID
        int channel_id;//Ƶ������ID
        int type_ids[10];//���ͷ���ID,һ����Ƶ�����10������
        int area_id;//����ID
        char video_name[20];//��Ƶ����
        int  play_times;//���Ŵ���
        char is_new; //0-����Ƶ 1-����Ƶ
        char video_image[25]; //��Ƶ����ͼƬ���ӵ�ַ
        char video_address[25]; //��Ƶ�������ӵ�ַ
}video_list_t;



//
//��Ƶ���ͷ���Ӧ���
typedef struct reply_type
{
        int type_count;//��Ƶ���ͷ�������
        int channel_id;//��ƵƵ��ID
        int type_id;//��Ƶ����ID
        char type_name[10];//��Ƶ������
}reply_type_t;

//0x04
//��������Ӧ���
typedef struct
{
        int area_count;//��Ƶ������������
        int channel_id;//��ƵƵ������ID
        int area_id;//��Ƶ��������ID
        char area_name[10];//��Ƶ������������
}reply_area;

//0x05
//��Ƶ�б�
typedef struct
{
        char VideoName[20];//��Ƶ��
}reply_list;




//0x06
//��Ƶ�㲥����
typedef struct
{
    int state;
    char updata_flowid[32];//
}reply_play;



//
typedef struct Log_st
{
    int reccount;//�������ݰ�
    int sendcount;//�������ݰ�
    int connectcount;//��Ч������
    int logincount;//�û���¼ҵ����
    int getvlistcount;//��ȡ��Ƶ�б���
    int getvrecordcount;//��ȡ�û����ż�¼ҵ����
    int uploadrcount;//�ϴ���Ƶ�㲥��¼ҵ����
    int uploadtimecount;//�ϴ���Ƶ�㲥ʱ����¼ҵ����
}Log_t;



#endif // PUBLICPACKET_H
