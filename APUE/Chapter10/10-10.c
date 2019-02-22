#include "../include/apue.h"

void sig_alrm(int signo)
{
    //do nothing, just return to interrupt the read
}

int main()
{
    int n;
    char line[MAXLINE];

    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        err_sys("signal error");

    alarm(10);//等待10秒
    if((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
        err_sys("read error");

    alarm(0);

    write(STDOUT_FILENO, line, n);
    return 0;
}
