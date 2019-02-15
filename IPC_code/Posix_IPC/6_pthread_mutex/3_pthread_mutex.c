#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

int run_now=1;  /*用run_now代表共享资源*/
pthread_mutex_t work_mutex;  /*定义互斥量*/

void *thread_function(void *arg)
{
    sleep(1);
    
    /*对互斥量加锁*/
    if(pthread_mutex_lock(&work_mutex)!=0)
    {
        perror("Lock failed");
        exit(1);
    }
    else
        printf("function lock\n");

    for (int i=0; i<5; i++)
    {
        /*分线程：如果run_now为1就把它修改为1*/
        if(run_now==2)  
        {
            printf("function thread is run\n");
            run_now=1;
        }
        else
        {
            printf("function thread is sleep\n");
            sleep(1);
        }
    }
    
    /*对互斥量解锁*/
    if(pthread_mutex_unlock(&work_mutex)!=0)  
    {
        perror("unlock failed");
        exit(1);
    }
    else
        printf("function unlock\n");

    pthread_exit(NULL);
}

int main()
{
    pthread_t a_thread;
     
    if(pthread_mutex_init(&work_mutex,NULL)!=0)  /*初始化互斥量*/
    {
        perror("Mutex init faied");
        exit(1);
    }

    if(pthread_create(&a_thread,NULL,thread_function,NULL)!=0)  /*创建新线程*/
    {
        perror("Thread createion failed");
        exit(1);
    }

    if(pthread_mutex_lock(&work_mutex)!=0)  /*对互斥量加锁*/
    {
        perror("Lock failed");
        exit(1);
    }
    else
        printf("main lock\n");
     

    for (int i=0; i<5; i++)
    {
        if(run_now == 1)  /*主线程：如果run_now为1就把它修改为2*/
        {
            printf("main thread is run\n");
            run_now=2;
        }
        else
        {
            printf("main thread is sleep\n");
            sleep(1);
        }
    }

    if(pthread_mutex_unlock(&work_mutex)!=0) /*对互斥量解锁*/
    {
        perror("unlock failed");
        exit(1);
    }
    else
        printf("main unlock\n");

    pthread_join(a_thread,NULL); /*等待子线程结束*/
    pthread_mutex_destroy(&work_mutex); /*收回互斥量资源*/

    exit(0);
}

 

