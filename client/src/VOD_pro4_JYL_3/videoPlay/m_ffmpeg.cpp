#include "m_ffmpeg.h"
#include <QDebug>

static double r2d(AVRational r)
{
    return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

m_FFmpeg::m_FFmpeg(QObject *parent) :
    QObject(parent)
{
    av_register_all();//ע��������п��õ��ļ���ʽ�ͽ�����
    avformat_network_init();//��ʼ����������ʽ,ʹ��RTSP������ʱ������ִ��
     m_Afc = avformat_alloc_context();//����һ��AVFormatContext�ṹ���ڴ�,�����м򵥳�ʼ��
    this->m_IsPlay = false;
}

m_FFmpeg::~m_FFmpeg()
{
    avformat_free_context(m_Afc);
    av_frame_free(&m_Yuv);
    sws_freeContext(m_VCtx);
}

int m_FFmpeg::open_Video(const QString path)
{

    closeForeVideo();
    m_Mtx.lock();

    //
    int n_Ret = avformat_open_input(&m_Afc,path.toStdString().c_str(),NULL,NULL);
    qDebug() << "open : " << path.toStdString().c_str();


    if (n_Ret < 0)
    {
        qDebug() << n_Ret;
        m_Mtx.unlock();
        char buf[1024] = {0};
        av_strerror(n_Ret,buf,sizeof(buf));//����Ƶ��ʧ��
        qDebug() << "open error";
        return 0;
    }

    n_Ret = avformat_find_stream_info(m_Afc,NULL);
    if(n_Ret < 0)
    {

        qDebug()<<"open stream erro";
        return 0;
    }

    av_dump_format(m_Afc, 0, path.toStdString().c_str(), false);


    m_Total_Ms = (m_Afc->duration / AV_TIME_BASE) * 1000;  //��Ƶ��ʱ�䣬����Ƕ��ٺ���
    //�򿪽�����
    //nb_streams�򿪵���Ƶ�ļ�������������һ��nb_streams = 2����Ƶ������Ƶ��
    for(unsigned int i = 0 ; i < m_Afc->nb_streams; i++)
    {
        AVCodecContext* acc = m_Afc->streams[i]->codec;
        if(acc->codec_type == AVMEDIA_TYPE_VIDEO)//��Ƶ��
        {
            m_VideoStream = i;
            AVCodec* codec = avcodec_find_decoder(acc->codec_id);// ������
            if (!codec)//"û�и����͵Ľ�����"
            {
                qDebug() << "û�и����͵Ľ�����";
                m_Mtx.unlock();
                qDebug() << "û�и����͵Ľ�����";
                return 0;
            }
            int err = avcodec_open2(acc, codec, NULL); //�򿪽�����
            if(err != 0)//��������ʧ��
            {
                m_Mtx.unlock();
                char buf[1024] = {0};
                av_strerror(err,buf,sizeof(buf));//����Ƶ��ʧ��
                return 0 ;
            }
        }
        else if(acc->codec_type == AVMEDIA_TYPE_AUDIO)//��Ƶ��
        {
            m_AudioStream = i;
            AVCodec *codec = avcodec_find_decoder(acc->codec_id);
            int aRet = avcodec_open2(acc, codec, NULL);
            if (aRet < 0)
            {
                qDebug() << "audio error";
                m_Mtx.unlock();
                return 0 ;
            }
            //������Ƶ����
            this->m_SampleRate = acc->sample_rate;//����Ƶ��
            this->m_Channel = acc->channels;
            switch(acc->sample_fmt)//������С
            {
            case AV_SAMPLE_FMT_S16:
                this->m_SampleSize = 16;
                break;
            case AV_SAMPLE_FMT_S32:
                this->m_SampleSize = 32;
                break;
            default:
                break;
            }
        }
    }
    m_Mtx.unlock();
    return m_Total_Ms;
}

int m_FFmpeg::decode_Frame(const AVPacket *packet)
{
    m_Mtx.lock();
    if (!m_Afc)
    {
        m_Mtx.unlock();
        return 0;
    }

    if(m_Yuv == NULL)
        m_Yuv = av_frame_alloc();
    if(m_Pcm == NULL)
        m_Pcm = av_frame_alloc();


    AVFrame *frame = m_Yuv;
    if(packet->stream_index == m_AudioStream)
    {
        frame = m_Pcm;
    }

    int re = avcodec_send_packet(m_Afc->streams[packet->stream_index]->codec, packet);
    if (re != 0)
    {
        m_Mtx.unlock();
        return 0;
    }

    re = avcodec_receive_frame(m_Afc->streams[packet->stream_index]->codec, frame);
    if (re != 0)
    {
        //ʧ��
        m_Mtx.unlock();
        return 0;
    }

    //    int frameFinished = 0;
    //   avcodec_decode_video2(m_Afc->streams[m_VideoStream]->codec, frame, &frameFinished, packet);
    //    if (frameFinished != 0)
    //    {
    //        m_Mtx.unlock();
    //        return;
    //    }

    int p = (frame->pts * r2d(m_Afc->streams[packet->stream_index]->time_base)) * 1000; //������
    if (packet->stream_index == m_AudioStream)
    {
        this->m_Pts = p;
    }
    m_Mtx.unlock();
    return p;
}


AVPacket m_FFmpeg::read_Frame()
{
    AVPacket packet;
    memset(&packet, 0, sizeof(AVPacket));

    m_Mtx.lock();
    if (!m_Afc)
    {
        m_Mtx.unlock();
        return packet;
    }

    av_read_frame(m_Afc, &packet);
    m_Mtx.unlock();

    return  packet;
}


bool m_FFmpeg::YuvToRGB(char *out, int outWeight, int outHeight)
{
    m_Mtx.lock();
    if (!m_Afc || !m_Yuv) //����ת����ǰ������Ƶ�Ѿ���
    {
        m_Mtx.unlock();
        return false;
    }

    AVCodecContext *videoCtx = m_Afc->streams[this->m_VideoStream]->codec;
    m_VCtx = sws_getCachedContext(m_VCtx, videoCtx->width, videoCtx->height,
                                  videoCtx->pix_fmt,  //���ص�ĸ�ʽ
                                  outWeight, outHeight,  //Ŀ������߶�
                                  AV_PIX_FMT_BGRA,  //����ĸ�ʽ
                                  SWS_BICUBIC,  //�㷨���
                                  NULL, NULL, NULL
                                  );

    if (m_VCtx)
    {
        //sws_getCachedContext �ɹ�"
    }
    else
    {
        //"sws_getCachedContext ʧ��"
    }

    uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };

    data[0] = (uint8_t *)out;  //ָ�봫ֵ���βε�ֵ�ᱻ�ı䣬out��ֵһֱ�ڱ䣬����QImageÿ�εĻ��涼��һ���������������ʾ�����ˣ���Ӧ�������������������ѵĵ�
    int linesize[AV_NUM_DATA_POINTERS] = { 0 };
    linesize[0] = outWeight * 4;  //ÿһ��ת��Ŀ��

    //����ת���ĸ߶�
    sws_scale(m_VCtx, m_Yuv->data, m_Yuv->linesize, 0, videoCtx->height,
              data,
              linesize
              );

    m_Mtx.unlock();
    return true;
}


int m_FFmpeg::toPCM(char *out)
{
    m_Mtx.lock();
    if(!m_Afc || !m_Pcm || !out)
    {
        m_Mtx.unlock();
        return 0;
    }

    AVCodecContext* ctx = m_Afc->streams[m_AudioStream]->codec;
    if(m_ACtx == NULL)
    {
        m_ACtx = swr_alloc();
        swr_alloc_set_opts(m_ACtx,ctx->channel_layout,
                           AV_SAMPLE_FMT_S16,
                           ctx->sample_rate,
                           ctx->channels,
                           ctx->sample_fmt,
                           ctx->sample_rate,
                           0,0);

        swr_init(m_ACtx);
    }

    uint8_t* data[1];
    data[0] = (uint8_t*)out;
    int len = swr_convert(m_ACtx,data,10000, (const uint8_t **)m_Pcm->data, m_Pcm->nb_samples);
    if(len < 0)
    {
        m_Mtx.unlock();
        return 0;
    }
    int outsize = av_samples_get_buffer_size(NULL, ctx->channels, m_Pcm->nb_samples, AV_SAMPLE_FMT_S16, 0);

    m_Mtx.unlock();
    return outsize;
}


void m_FFmpeg::closeForeVideo()
{
    m_Mtx.lock();

    if(m_Afc)
        avformat_close_input(&m_Afc);
    if(m_Yuv)
        av_frame_free(&m_Yuv);
    if(m_VCtx)
    {
        sws_freeContext(m_VCtx);
        m_VCtx = NULL;
    }
    if(m_ACtx)
        swr_free(&m_ACtx);

    m_Mtx.unlock();
}



bool m_FFmpeg::seek(float pos)
{
    m_Mtx.lock();
    if(!m_Afc)
    {
        m_Mtx.unlock();
        return false;
    }

    int64_t stamp = 0;
    stamp = pos * m_Afc->streams[m_VideoStream]->duration;//��ǰ��ʵ�ʵ�λ��

    m_Pts = stamp * r2d(m_Afc->streams[m_VideoStream]->time_base);//��û������������ʱ���
    int re = av_seek_frame(m_Afc, m_VideoStream, stamp, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME); //����Ƶ��������ǰλ��

    //���֮ǰ�Ľ��뻺��
    avcodec_flush_buffers(m_Afc->streams[m_VideoStream]->codec);//ˢ�»���,�����
    m_Mtx.unlock();
    if (re >= 0)
    {
        return true;
    }
    //�ؼ�֡��P֡�� B֡
    return false;
}



int m_FFmpeg::getPts(const AVPacket *packet)
{
    m_Mtx.lock();
    if (!m_Afc)
    {
        m_Mtx.unlock();
        return -1;
    }
    int pts = (packet->pts * r2d(m_Afc->streams[packet->stream_index]->time_base)) * 1000; //������
    m_Mtx.unlock();
    return pts;
}



