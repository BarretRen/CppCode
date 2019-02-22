#include "../include/apue.h"
#include <pthread.h>

int main()
{
    int err;
    struct timespec time;
    struct tm* tmp;
    char buf[64];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&lock);
    printf("mutex is locked\n");

    clock_gettime(CLOCK_REALTIME, &time);
    tmp = localtime(&time.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("current time is %s\n", buf);
    time.tv_sec += 10; //十秒后

    err = pthread_mutex_timedlock(&lock, &time);

    clock_gettime(CLOCK_REALTIME, &time);
    tmp = localtime(&time.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("current time is %s\n", buf);

    if (err == 0)
        printf("mutex locked again\n");
    else
        printf("can't lock mutex again:%s\n", strerror(err));

    return 0;
}
