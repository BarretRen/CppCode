#include "../include/apue.h"
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
        err_sys("fork failed");
    else if (pid == 0)
        exit(7);//子进程直接退出，返回状态7

    if (wait(&status) != pid)//等待子进程退出，同时获取状态
        err_sys("wait error");
    pr_exit(status);


    if ((pid = fork()) < 0)
        err_sys("fork failed");
    else if (pid == 0)
        abort();//子进程直接退出，产生SIGABRT信号

    if (wait(&status) != pid)//等待子进程退出，同时获取状态
        err_sys("wait error");
    pr_exit(status);



    if ((pid = fork()) < 0)
        err_sys("fork failed");
    else if (pid == 0)
        status /= 0;//除以0，导致子进程直接退出，产生SIGFPE信号

    if (wait(&status) != pid)//等待子进程退出，同时获取状态
        err_sys("wait error");
    pr_exit(status);

    return 0;
}
