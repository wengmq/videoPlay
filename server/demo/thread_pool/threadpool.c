#include "threadpool.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

void *thread_routine(void *arg)
{
	struct timespec abstime;
	threadpool_t *pool = (threadpool_t *)arg;
	printf("thread 0x%x is starting\n", (int)pthread_self());

	//1. 设置为自分离线程
	pthread_detach(pthread_self());

	//3. 进入轮询工作模式，如果不退出且队列不为空则一直工作
	while(1)
	{
		//1. 先去看下有没有任务，有任务则处理任务，没有再wait
		condition_lock(&pool->ready);
		printf("thread 0x%x is working\n", (int)pthread_self());
		if(pool->first != NULL)
		{
			task_t *t = pool->first; 	//取出第一个任务
			pool->first = t->next;   	//修改队列头
			condition_unlock(&pool->ready); //先解锁，提高效率

			//处理任务
			t->run(t->arg);
			free(t);
			continue; //既然本次有任务，可能下次还有任务，则继续查看是否有任务
		}
		else
		{
			condition_unlock(&pool->ready);
		}
		
		if(pool->quit)
		{
			break;
		}

		//2. 如果没有任务，则等待
		printf("thread 0x%x is waiting\n", (int)pthread_self());
		while(1)
		{
			clock_gettime(CLOCK_REALTIME, &abstime);
			abstime.tv_sec += 2; //延时2s
			//condition_wait(&pool->ready);
			condition_lock(&pool->ready);
			pool->idle++;
			int status = condition_timedwait(&pool->ready, &abstime);
			condition_unlock(&pool->ready);
			if (status != ETIMEDOUT || pool->quit)
			{
				printf("thread 0x%x get signal\n", (int)pthread_self());
				break;
			}
			else
			{
				printf("thread 0x%x is wait timed out\n", (int)pthread_self());
				if(pool->counter >= 3)
				{
					goto THREAD_EXIT;
				}
			}			
		}
	}
	
THREAD_EXIT:	
	printf("thread 0x%x is exit\n", (int)pthread_self());
	condition_lock(&pool->ready);
	pool->counter--;
	condition_unlock(&pool->ready);
	pthread_exit(NULL); //退出线程
}

void threadpool_init(threadpool_t **pool, int threads)
{
	//1. 初始化基本的线程池参数
	int i;
	threadpool_t *newpool = malloc(sizeof(threadpool_t));
	
	*pool = newpool;
	newpool->max_threads = threads;
	newpool->quit = 0;
	newpool->idle = 0; //??
	newpool->first = NULL;
	newpool->last = NULL;
	newpool->counter = 0;
	condition_init(&newpool->ready);

	//2. 默认有线程数，则在初始化的时候同时初始化N个线程
#if 1	
	for(i= 0; i < 5; i++)
	{
		pthread_t tid;
		if(pthread_create(&tid, NULL, thread_routine, newpool) == 0)//where is task?
		{
			condition_lock(&newpool->ready);
			newpool->counter++;
			condition_unlock(&newpool->ready);
		}
	}
#endif	
}

void threadpool_add_task(threadpool_t *pool, void *(*run)(void *arg), void *arg)
{
	if(pool->quit)
		return;

	//1. 生成任务包
	task_t *task = malloc(sizeof(task_t));
	task->run = run;
	task->arg = arg;

	//2. 加到task队列， 先上锁，再添加，再解锁
	printf("Add new task %p ! \n", task);
	condition_lock(&pool->ready);
	if(pool->last == NULL)
	{
		pool->last = task; //队列头
		pool->first = pool->last; //初始化头
	}
	else
	{
		pool->last->next = task; // add
		pool->last = task;
	}

	//3. 计算一下线程数是否满足任务处理速度，不满足则创建一批
	if(pool->counter < pool->max_threads && pool->idle <= 0)
	{
		//？？线程创建策略，根据实际环境选择
		//	策略1： 固定增长，每次增长??
		//	策略2： 指数增长，每次翻倍?? 也就是创建 pool->counter
		//	策略3： 线下增长，每次+1
		//  策略4： 根据任务数量增长
		pthread_t tid;
		if(pthread_create(&tid, NULL, thread_routine, pool) == 0) //where is task?
		{
			pool->counter++;
		}
	}

	//4. 通知线程去取任务处理
	if(pool->idle > 0)
	{
		condition_signal(&pool->ready); //唤醒一个线程去处理任务
	}

	//5. 解锁
	condition_unlock(&pool->ready);
}

void threadpool_destroy(threadpool_t *pool)
{
	//1. 设置退出条件
	pool->quit = 1;

	//2. 等待所有线程退出
	while(pool->counter > 0)
	{
		//3. 广播，通知所有线程退出
		condition_lock(&pool->ready);
		condition_broadcast(&pool->ready); //唤醒所有线程退出
		condition_unlock(&pool->ready);
		sleep(1);
	}

	//4. 销毁线程池对象
	free(pool);
}

