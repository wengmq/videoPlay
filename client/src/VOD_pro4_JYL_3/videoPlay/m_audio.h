#ifndef M_AUDIO_H
#define M_AUDIO_H

#include <QObject>
#include <QMutex>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimedia/QAudioFormat>
#include <QIODevice>
class m_Audio : public QObject
{
    Q_OBJECT
public:
    explicit m_Audio(QObject *parent = 0);
    ~m_Audio();
    void stop();
    bool start();
    void play(bool isPlay);
    bool write(const char* data , int  datasize);
    int getFree();

public:
    int sampleRate;
    int sampleSize;
    int channel;

    QAudioOutput* output;
    QIODevice* io;
    QMutex mutex;

public :
    static m_Audio* getObj()
    {
        static m_Audio m_AU;
        return &m_AU;
    }

signals:

public slots:

};

#endif // M_AUDIO_H
