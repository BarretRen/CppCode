#include "../include/apue.h"

void my_exit1()
{
    printf("first exit handler\n");
}

void my_exit2()
{
    printf("second exit handler\n");
}

int main()
{
    //注册终止处理函数, 注册顺序和执行顺序相反
    if (atexit(my_exit2) != 0)
        err_sys("cannot register my_exit2");

    if (atexit(my_exit1) != 0)
        err_sys("cannot register my_exit1");

    printf("main is done\n");
    return 0;
}
