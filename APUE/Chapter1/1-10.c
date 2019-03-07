#include "../include/apue.h"
#include <sys/wait.h>

void sig_handler(int signal)
{
    printf("interrupt\n");
}

int main()
{
    char buf[MAXLINE];
    int status;
    pid_t pid;

    //注册自定义函数
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        err_sys("signal error");

    printf("%%");
    while(fgets(buf, MAXLINE, stdin) != NULL)
    {
        if(buf[strlen(buf) - 1] =='\n')
            buf[strlen(buf) - 1 ] =0;

        pid = fork();
        if (pid < 0)
            err_sys("fork error");
        else if (pid == 0) //child process
        {
            execlp(buf, buf, (char*)0);
            err_ret("could not execure: %s", buf);
            exit(127);
        }

        if((pid == waitpid(pid, &status, 0)) < 0)
            err_sys("waitpid failed");

        printf("%%");
    }

    return 0;
}
