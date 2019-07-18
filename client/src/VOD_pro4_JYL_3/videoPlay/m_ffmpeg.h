#ifndef M_FFMPEG_H
#define M_FFMPEG_H

#include <QObject>
#include <QMutex>
#include <QDebug>


//引入ffmpeg头文件
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
#include <libswscale/swscale.h>
#include <libavutil/frame.h>
#include <libswresample/swresample.h>
}

class m_FFmpeg : public QObject
{
    Q_OBJECT
public:
    explicit m_FFmpeg(QObject *parent = 0);
    ~m_FFmpeg();

    int open_Video(const QString path);
    int decode_Frame(const AVPacket *packet);
    AVPacket read_Frame();
    bool YuvToRGB(char* out , int outWeight,int outHeight);
    int toPCM(char* out);
    void closeForeVideo();
    bool seek(float pos);
    int getPts(const AVPacket *packet);
public:
    static m_FFmpeg *getObj()
    {
        static m_FFmpeg m_FF;
        return &m_FF;
    }
public :
    bool m_IsPlay;   //播放开关
    AVFrame* m_Yuv;  //解码后的视频帧数据
    AVFrame* m_Pcm;  //解码后的音频帧数据

    SwsContext* m_VCtx; //视频转码上下文
    SwrContext *m_ACtx; //音频转码上下文

    int m_SampleRate; //miniDV、数字电视、DVD、DAT、电影和专业音频所用的数字声音所用采样率
    int m_SampleSize;  //声卡16位
    int m_Channel;      //双通道

    int m_VideoStream;
    int m_AudioStream;

    int m_Pts;//当前视频播放进度
    int m_Total_Ms;//总时长

protected:
    AVFormatContext* m_Afc;//解封装上下文
    QMutex m_Mtx;//互斥锁
signals:

public slots:

};

#endif // M_FFMPEG_H
