#include "m_audio.h"

m_Audio::m_Audio(QObject *parent) :
    QObject(parent)
{

}

m_Audio::~m_Audio()
{
}

void m_Audio::stop()
{
    mutex.lock();
    if(output)
    {
        output->stop();
        delete output;
        output = NULL;
        io = NULL;
    }
    mutex.unlock();
}

bool m_Audio::start()
{
    stop();
    mutex.lock();
    QAudioFormat fmt; //Qt��Ƶ��ʽ
    fmt.setSampleRate(this->sampleRate);//1��ɼ�48000������
    fmt.setSampleSize(this->sampleSize);//16λ
    fmt.setChannelCount(this->channel);//����2˫����
    fmt.setByteOrder(QAudioFormat::LittleEndian);//����
    fmt.setCodec("audio/pcm");           //��Ƶ�ĸ�ʽ
    fmt.setByteOrder(QAudioFormat::LittleEndian); //����
    fmt.setSampleType(QAudioFormat::UnSignedInt); //���������

    output = new QAudioOutput(fmt);
    io = output->start();
    mutex.unlock();
    return true;
}

void m_Audio::play(bool isPlay)
{
    mutex.lock();
    if (!output)
    {
        mutex.unlock();
        return;
    }

    if (isPlay)
    {
        output->resume();
    }
    else
    {
        output->suspend();
    }

    mutex.unlock();
}

//��������豸��������
bool m_Audio::write(const char *data, int datasize)
{
    if (!data || datasize <= 0)
        return false;
    mutex.lock();
    if (io)
    {
        mutex.unlock();
        io->write(data, datasize); //��������豸��������,�����ݴ�����ֹ��8λ�ַ��ַ���д���豸��
        return true;
    }

    mutex.unlock();
}

int m_Audio::getFree()
{
    mutex.lock();
    if (!output)
    {
        mutex.unlock();
        return 0;
    }

    int free = output->bytesFree();
    mutex.unlock();

    return free;
}
