#ifndef CPTHREADMUTEX_H
#define CPTHREADMUTEX_H

#include <stdio.h>
#include <pthread.h>

class CPThreadMutex
{
public:
    CPThreadMutex();
    ~CPThreadMutex();
    bool lock();//上锁
    bool unlock();
    bool trylock();
protected:
    pthread_mutex_t m_mutex;
};

#endif // CPTHREADMUTEX_H
