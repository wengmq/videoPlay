#ifndef M_FFMPEG_H
#define M_FFMPEG_H

#include <QObject>
#include <QMutex>
#include <QDebug>


//����ffmpegͷ�ļ�
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
    bool m_IsPlay;   //���ſ���
    AVFrame* m_Yuv;  //��������Ƶ֡����
    AVFrame* m_Pcm;  //��������Ƶ֡����

    SwsContext* m_VCtx; //��Ƶת��������
    SwrContext *m_ACtx; //��Ƶת��������

    int m_SampleRate; //miniDV�����ֵ��ӡ�DVD��DAT����Ӱ��רҵ��Ƶ���õ������������ò�����
    int m_SampleSize;  //����16λ
    int m_Channel;      //˫ͨ��

    int m_VideoStream;
    int m_AudioStream;

    int m_Pts;//��ǰ��Ƶ���Ž���
    int m_Total_Ms;//��ʱ��

protected:
    AVFormatContext* m_Afc;//���װ������
    QMutex m_Mtx;//������
signals:

public slots:

};

#endif // M_FFMPEG_H
