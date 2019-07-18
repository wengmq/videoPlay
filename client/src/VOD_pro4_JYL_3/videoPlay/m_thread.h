#ifndef M_THREAD_H
#define M_THREAD_H

#include <QObject>
#include <QThread>
#include "m_ffmpeg.h"
#include "m_audio.h"
#include <QList>


class m_Thread : public QThread
{
    Q_OBJECT
public:
    explicit m_Thread(QObject *parent = 0);
    ~m_Thread();
    void run();

public:
    static m_Thread* getObj()
    {
        static m_Thread m_TH;
        return &m_TH;
    }

signals:

public slots:

};

#endif // M_THREAD_H

