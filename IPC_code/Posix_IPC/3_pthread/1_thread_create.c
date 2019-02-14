#include "common.h"
#include <pthread.h>

void* thread_function(void* arg)
{
    for (int i=0; i<20; i++)
    {
        printf("slave thread said B\n");
        fflush(stdout);
        usleep(20);
    }
    sleep(3);
    return 0;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, thread_function, NULL);
    if (ret != 0)
    {
        //错误处理
        printf("pthread_create failed, error message: %s\r\n", strerror(ret));
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<20; i++)
    {
        printf("master thread said A\n");
        fflush(stdout);
        usleep(20);
    }

    //主线程等待新创建的线程结束，不然会直接终止
    ret = pthread_join(tid, NULL);
    if (ret != 0)
    {
        //错误处理
        printf("pthread_join failed, error message: %s\r\n", strerror(ret));
        exit(EXIT_FAILURE);
    }

    return 0;
}
