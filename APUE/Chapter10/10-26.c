#include "../include/apue.h"

void sig_int(int signo)
{
    printf("cautght SIGINT\n");
}

void sig_child(int signo)
{
    printf("caught SIGCHLD\n");
}

int main()
{
    if (signal(SIGINT, sig_int) == SIG_ERR)
        err_sys("signal SIGINT error");
    if (signal(SIGCHLD, sig_child) == SIG_ERR)
        err_sys("signal SIGCHLD error");

    if (system("/bin/ed") < 0)
        err_sys("system error");

    return 0;
}
