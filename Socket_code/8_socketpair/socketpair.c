#include "common.h"

int main()
{
    int socks[2];
    if(socketpair(PF_UNIX, SOCK_STREAM, 0, socks) < 0)
        ERR_EXIT("socketpair failed");

    pid_t pid;
    pid = fork();
    if (pid > 0)
    {
        //父进程
        int val = 0;
        close(socks[1]);//只需要保留一个socket在该进程，另一个在另一进程
        while(1)
        {
            ++val;
            printf("send data: %d\r\n", val);
            write(socks[0], &val, sizeof(val));
            read(socks[0], &val, sizeof(val));
            printf("receive data: %d\r\n", val);
            sleep(1);
        }
    }
    else if (pid == 0)
    {
        int val;
        close(socks[0]);
        while(1)
        {
            read(socks[1], &val, sizeof(val));
            ++val;
            write(socks[1], &val, sizeof(val));
        }
    }
    return 0;
}
