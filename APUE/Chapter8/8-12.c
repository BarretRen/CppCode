#include "../include/apue.h"

void charatatime(char* str)
{
    char* p;
    int c;
    setbuf(stdout, NULL);//设置标准输出为无缓冲
    for (p = str; (c = *p++) != 0;)
        putc(c, stdout);
}

int main()
{
    pid_t pid;

    if ((pid = fork()) < 0)
        err_sys("fork failed");
    else if (pid == 0)
        charatatime("output from child\n");
    else
        charatatime("outout from parent\n");

    return 0;
}
