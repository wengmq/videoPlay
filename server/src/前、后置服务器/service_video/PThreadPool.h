#ifndef PTHREADPOOL_H
#define PTHREADPOOL_H

#include <list>
#include "PThreadCond.h" //条件变量
#include <unistd.h>

using namespace std;

class CTask
{
public:
	CTask(){}
	virtual ~CTask(){}
	virtual int run()=0;
};
// class myCTask:public CTask
// {
// 	int run()
// 	{
// 		sleep(30);
// 	}
// };

typedef list<CTask *> list_task;
class CThreadPool
{
public:
	CThreadPool(unsigned int max=77,unsigned int min=77,unsigned int wait=60);
	~CThreadPool();
	void addTask(CTask *task);
	void createThread();	
	void start(unsigned NumCreate);// Create a num of thread
	void destroy();
	
//private:
    void setTaskName(char *acName); 
	static void *taskThread(void *arg);// work thread
	unsigned int m_maxcount;
	unsigned int m_mincount;
	unsigned int m_count;
	unsigned int m_waitcount;
	unsigned int m_waitsec;
	list_task  	 m_taskList;
	CPThreadCond m_taskCond;
	CPThreadCond m_cond;
	bool m_bStop;
};



#endif