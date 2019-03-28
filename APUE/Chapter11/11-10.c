#include <stdlib.h>
#include <pthread.h>

struct foo
{
    int count;
    pthread_mutex_t lock;
    int id;
    //其他成员
};

struct foo* foo_alloc(int id)
{
    struct foo* fp;
    if ((fp = malloc(sizeof(struct foo))) != NULL)
    {
        fp->count = 1;//初始计数为1，当前有一个主线程
        fp->id = id;
        if (pthread_mutex_init(&(fp->lock), NULL) != 0)
        {
            //初始化互斥量失败，退出
            free(fp);
            return NULL;
        }
    }
    return fp;
}

void foo_add(struct foo* fp)
{
    //互斥量锁定，计数加一
    pthread_mutex_lock(&
}
