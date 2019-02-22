#include "../include/apue.h"

void sig_quit(int signo)
{
    printf("caught SIGQUIE\n");
    if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
        err_sys("cannot reset SIGQUIT");
}

int main()
{
    sigset_t newmask, oldmask, pendmask;

    //note: SIGQUIT = Ctrl + \
    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
        err_sys("cannot catch SIGQUIT");
    
    //block SIGQUIT and save current signal mask
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("SIG_BLOCK error");

    sleep(5); //因为上面设置mask，SIGQUIT被屏蔽，所以一直处于pending
    if (sigpending(&pendmask) < 0)
        err_sys("sigpending error");
    if (sigismember(&pendmask, SIGQUIT))
        printf("SIGQUIT is pending\n");

    //恢复mask
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("UNBLOCK error");
    printf("SIGQUIT unblocked\n");

    sleep(5); //SIGQUIT here will terminate with core file
    return 0;
}
