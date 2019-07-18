/*************************************************************************
	> File Name: test.cpp
	> Author: eric
	> Mail: 
	> Created Time: 2017年11月23日 星期四 02时42分06秒
 ************************************************************************/

#include <iostream>
#include "BaseThread.h"

using namespace std;

class CmyThread: public CBaseThread
{
public:
    CmyThread(int value);
    ~CmyThread();
    int run(); //重写
private:
    int m_iValue;
};

CmyThread::CmyThread(int value)
{
    m_iValue =  value;
}

CmyThread::~CmyThread()
{
    
}

int CmyThread::run()
{
    printf("this is thread, value = %d\n", m_iValue);
    return 0;
}

int main(int argc, char* argv[])
{
    CmyThread myThread(2);
    myThread.start();

    sleep(1);
    return 0;
}


