#include "m_thread.h"

static QList<AVPacket> g_Videos; //存放视频帧
static int apts = -1;//音频的pts
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
    while(true)//线程未退出
    {
        if(!m_FFmpeg::getObj()->m_IsPlay)//如果为暂停状态，不处理
        {
            msleep(10);//处理点击播放
            continue;
        }
        while(g_Videos.size() > 0)
        {
            AVPacket pack = g_Videos.front();
            int pts = m_FFmpeg::getObj()->getPts(&pack);
            if(pts > apts)//若视频包大于音频包的pts，结束
            {
                break;
            }
            m_FFmpeg::getObj()->decode_Frame(&pack);//解码视频帧
            av_packet_unref(&pack);//清理该AVPacket包
            g_Videos.pop_front();//解码完成的帧从前面弹出list
        }
        int free = m_Audio::getObj()->getFree();//此时缓冲区的空间大小
        if(free < 10000)
        {
            msleep(1);
            continue;
        }
        AVPacket pkt = m_FFmpeg::getObj()->read_Frame();
        if(pkt.size <= 0 )//未打开视频
        {
            msleep(10);
            continue;
        }
        if(pkt.stream_index == m_FFmpeg::getObj()->m_AudioStream)
        {
            apts = m_FFmpeg::getObj()->decode_Frame(&pkt);
            av_packet_unref(&pkt);
            int len = m_FFmpeg::getObj()->toPCM(out);//转换音频
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
