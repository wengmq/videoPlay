#include "m_thread.h"

static QList<AVPacket> g_Videos; //�����Ƶ֡
static int apts = -1;//��Ƶ��pts
m_Thread::m_Thread(QObject *parent) :
    QThread(parent)
{
}

m_Thread::~m_Thread()
{
}

void m_Thread::run()
{
    char out[10000] = {0};
    while(true)//�߳�δ�˳�
    {
        if(!m_FFmpeg::getObj()->m_IsPlay)//���Ϊ��ͣ״̬��������
        {
            msleep(10);//����������
            continue;
        }
        while(g_Videos.size() > 0)
        {
            AVPacket pack = g_Videos.front();
            int pts = m_FFmpeg::getObj()->getPts(&pack);
            if(pts > apts)//����Ƶ��������Ƶ����pts������
            {
                break;
            }
            m_FFmpeg::getObj()->decode_Frame(&pack);//������Ƶ֡
            av_packet_unref(&pack);//�����AVPacket��
            g_Videos.pop_front();//������ɵ�֡��ǰ�浯��list
        }
        int free = m_Audio::getObj()->getFree();//��ʱ�������Ŀռ��С
        if(free < 10000)
        {
            msleep(1);
            continue;
        }
        AVPacket pkt = m_FFmpeg::getObj()->read_Frame();
        if(pkt.size <= 0 )//δ����Ƶ
        {
            msleep(10);
            continue;
        }
        if(pkt.stream_index == m_FFmpeg::getObj()->m_AudioStream)
        {
            apts = m_FFmpeg::getObj()->decode_Frame(&pkt);
            av_packet_unref(&pkt);
            int len = m_FFmpeg::getObj()->toPCM(out);//ת����Ƶ
            m_Audio::getObj()->write(out,len);
            continue;
        }

        if (pkt.stream_index != m_FFmpeg::getObj()->m_VideoStream)
        {
            av_packet_unref(&pkt);
            continue;
        }

        g_Videos.push_back(pkt);
    }

}
