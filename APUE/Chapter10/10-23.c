#include "../include/apue.h"

volatile sig_atomic_t quitflag;

void sig_int(int signo)
{
    if (signo == SIGINT)
        printf("\ninterrupt\n");
    else if (signo == SIGQUIT)
    {
        quitflag = 1;
    }
    printf("\nquitflag = %d\n", quitflag);
}

int main()
{
    sigset_t newmask, oldmask, zeromask;
    //signal 只能生效一次，这里用POSIX标准的sigaction，可移植
    struct sigaction act;
    act.sa_handler = sig_int;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART; //可以重复调用
    if (sigaction(SIGINT, &act, NULL) < 0)
        err_sys("signal SIGINT error");
    if (sigaction(SIGQUIT, &act, NULL) < 0)
        err_sys("signal SIGQUIT error");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    //阻塞SIGQUIT，保存当前mask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("sigprocmask error");

    while (quitflag == 0)
    {
        printf("in the while\n");
        //zeromask是空的，所以不会阻塞任何signal，sigsuspend可以接受任何消息，包括SIGQUIT
        sigsuspend(&zeromask); //收不到SIGQUIT，flag一直为0，循环继续
    }
    //循环跳出，表示收到的SIGQUIT信号
    quitflag = 0;

    //reset old mask
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");

    return 0;
}
