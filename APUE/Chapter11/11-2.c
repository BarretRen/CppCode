#include "../include/apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char* s)
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u %lu (0x%1x)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
} 

void* thread_func(void* arg)
{
    printids("new thread: ");
    return (void*)0;
}

int main()
{
    int err = pthread_create(&ntid, NULL, thread_func, NULL);
    if (err != 0)
        err_exit(err, "failed to create thread");

    printids("main thread: ");
    sleep(1);
    return 0;
}
