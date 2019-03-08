#include "../include/apue.h"

int glovar = 6;//初始化数据段的全局变量
char buf[]="a write to stdout\n";

int main()
{
    int var;//栈中的局部变量
    pid_t pid;
    var = 88;
    
    if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
        err_sys("write error");

    printf("before fork\n");
    pid = fork();
    if (pid < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        //子进程
        glovar++;
        var++;
    }
    else
    {
        //父进程
        sleep(2);
    }

    printf("pid = %ld, glovar = %d, var =%d\n", (long)getpid(), glovar, var);
    return 0;
}
