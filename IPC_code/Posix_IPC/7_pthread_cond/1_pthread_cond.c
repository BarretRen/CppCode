#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
 
#define ERR_EXIT(m) \
	do \
	{	\
		perror(m); \
		exit(EXIT_FAILURE); \
	}while(0)
	
#define CONSUMERS_COUNT 2
#define PRODUCERS_COUNT 4
 
pthread_cond_t g_cond;
pthread_mutex_t g_mutex;
 
// 创建的线程ID保存在g_thread中
pthread_t g_thread[CONSUMERS_COUNT+PRODUCERS_COUNT];
 
int nready=0;
 
///消费者
void* consume(void* arg)
{
    //most platforms pointers and longs are the same size, but ints and pointers often are not the same size on 64bit platforms
	int num = (long)arg;
	while(1)
	{
		pthread_mutex_lock(&g_mutex);
		while(nready == 0)
		{
			printf("(%d)begin wait a condition....\n",num);
			pthread_cond_wait(&g_cond,&g_mutex);
		}
		printf("(%d) end wait a condition....\n",num);
		printf("(%d) begin consume product ....\n",num);
		--nready;
		printf("(%d) end consume product ....\n",num);
		pthread_mutex_unlock(&g_mutex);
		sleep(1);
	}
	return NULL;
}
 
//// 生产者
void* produce(void* arg)
{
    //most platforms pointers and longs are the same size, but ints and pointers often are not the same size on 64bit platforms
	int num = (long)arg;
	while(1)
	{
		pthread_mutex_lock(&g_mutex);
		printf(" (%d) begin produce product ...\n",num);
		++nready;
		printf(" (%d) end produce product....\n",num);
		pthread_cond_signal(&g_cond);
		printf(" (%d) signal \n",num);
		pthread_mutex_unlock(&g_mutex);
		sleep(5);
	}
	return NULL;
}
 
int main(void )
{
	//初始化互斥锁
	pthread_mutex_init(&g_mutex,NULL);
	//初始化条件变量
	pthread_cond_init(&g_cond,NULL);
	
	/// 创建消费者线程
	for(int i=0; i<CONSUMERS_COUNT; i++)
		pthread_create(&g_thread[i],NULL,consume,(void*)i);
    
	sleep(1);
	/// 创建生产者线程
	for(int i=0; i<PRODUCERS_COUNT; i++)
		pthread_create(&g_thread[CONSUMERS_COUNT+i],NULL,produce,(void*)i);
    
	// 等待线程的结束	
	for(int i=0; i<CONSUMERS_COUNT+PRODUCERS_COUNT; i++)
		pthread_join(g_thread[i],NULL);
		
	//销毁互斥锁和条件变量	
	pthread_mutex_destroy(&g_mutex);
	pthread_cond_destroy(&g_cond);
	
	return 0;
}
