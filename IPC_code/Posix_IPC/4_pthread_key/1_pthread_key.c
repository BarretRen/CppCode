#include "common.h"
#include <pthread.h>

struct tsd
{
    pthread_t tid;
    char* str;
};

pthread_key_t key;
void destroy_func(void* value)
{
    //删除key时调用该函数
    printf("destroy the key here\n");
    free(value); //释放malloc的内存,这里value就是保存到key中的数据的指针
}

void* thread_func(void* arg)
{
    tsd* value = (tsd*)malloc(sizeof(tsd));
    value->tid = pthread_self();
    value->str = (char*)arg;
    //设置key的值
    printf("%s set the value[%p] of the key\n", (char*)arg, value);
    pthread_setspecific(key, value);
    //获取key中的值
    sleep(2);
    value = (tsd*)pthread_getspecific(key);
    printf("tid=0x%x, str=%s\n", value->tid, value->str);

    return NULL;
}
int main()
{
    key = pthread_key_create(&key, destroy_func);

    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, thread_func, (void*)"thread1");
    pthread_create(&t2, NULL, thread_func, (void*)"thread2");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
