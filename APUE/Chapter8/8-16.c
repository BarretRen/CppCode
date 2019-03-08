#include "../include/apue.h"
#include <sys/wait.h>

char* env[] = {"USER=unknown","PATH=/tmp", NULL};//需要以null结尾

int main()
{
    pid_t pid;

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        if (execle("./exfunc", "exfunc", "barret", "ren", (char*)0, env) < 0)
            err_sys("execle error");
    }

    if (waitpid(pid, NULL, 0) < 0)
        err_sys("waitpid error");

    return 0;
}
