#include "m_ffmpeg.h"
#include <QDebug>

static double r2d(AVRational r)
{
    return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

m_FFmpeg::m_FFmpeg(QObject *parent) :
    QObject(parent)
{
    av_register_all();//注册库中所有可用的文件格式和解码器
    avformat_network_init();//初始化网络流格式,使用RTSP网络流时必须先执行
     m_Afc = avformat_alloc_context();//申请一个AVFormatContext结构的内存,并进行简单初始化
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
        av_strerror(n_Ret,buf,sizeof(buf));//打开视频流失败
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


    m_Total_Ms = (m_Afc->duration / AV_TIME_BASE) * 1000;  //视频的时间，结果是多少豪秒
    //打开解码器
    //nb_streams打开的视频文件中流的数量，一般nb_streams = 2，音频流和视频流
    for(unsigned int i = 0 ; i < m_Afc->nb_streams; i++)
    {
        AVCodecContext* acc = m_Afc->streams[i]->codec;
        if(acc->codec_type == AVMEDIA_TYPE_VIDEO)//视频流
        {
            m_VideoStream = i;
            AVCodec* codec = avcodec_find_decoder(acc->codec_id);// 解码器
            if (!codec)//"没有该类型的解码器"
            {
                qDebug() << "没有该类型的解码器";
                m_Mtx.unlock();
                qDebug() << "没有该类型的解码器";
                return 0;
            }
            int err = avcodec_open2(acc, codec, NULL); //打开解码器
            if(err != 0)//解码器打开失败
            {
                m_Mtx.unlock();
                char buf[1024] = {0};
                av_strerror(err,buf,sizeof(buf));//打开视频流失败
                return 0 ;
            }
        }
        else if(acc->codec_type == AVMEDIA_TYPE_AUDIO)//音频流
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
            //设置视频参数
            this->m_SampleRate = acc->sample_rate;//采样频率
            this->m_Channel = acc->channels;
            switch(acc->sample_fmt)//样本大小
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
        //失败
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

    int p = (frame->pts * r2d(m_Afc->streams[packet->stream_index]->time_base)) * 1000; //毫秒数
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
    if (!m_Afc || !m_Yuv) //像素转换的前提是视频已经打开
    {
        m_Mtx.unlock();
        return false;
    }

    AVCodecContext *videoCtx = m_Afc->streams[this->m_VideoStream]->codec;
    m_VCtx = sws_getCachedContext(m_VCtx, videoCtx->width, videoCtx->height,
                                  videoCtx->pix_fmt,  //像素点的格式
                                  outWeight, outHeight,  //目标宽度与高度
                                  AV_PIX_FMT_BGRA,  //输出的格式
                                  SWS_BICUBIC,  //算法标记
                                  NULL, NULL, NULL
                                  );

    if (m_VCtx)
    {
        //sws_getCachedContext 成功"
    }
    else
    {
        //"sws_getCachedContext 失败"
    }

    uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };

    data[0] = (uint8_t *)out;  //指针传值，形参的值会被改变，out的值一直在变，所以QImage每次的画面都不一样，画面就这样显示出来了，这应该是整个开发过程最难的点
    int linesize[AV_NUM_DATA_POINTERS] = { 0 };
    linesize[0] = outWeight * 4;  //每一行转码的宽度

    //返回转码后的高度
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
    stamp = pos * m_Afc->streams[m_VideoStream]->duration;//当前它实际的位置

    m_Pts = stamp * r2d(m_Afc->streams[m_VideoStream]->time_base);//获得滑动条滑动后的时间戳
    int re = av_seek_frame(m_Afc, m_VideoStream, stamp, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME); //将视频移至到当前位置

    //清除之前的解码缓冲
    avcodec_flush_buffers(m_Afc->streams[m_VideoStream]->codec);//刷新缓冲,清理掉
    m_Mtx.unlock();
    if (re >= 0)
    {
        return true;
    }
    //关键帧，P帧， B帧
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
    int pts = (packet->pts * r2d(m_Afc->streams[packet->stream_index]->time_base)) * 1000; //毫秒数
    m_Mtx.unlock();
    return pts;
}



