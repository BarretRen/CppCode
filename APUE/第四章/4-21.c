#include "../include/apue.h"
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int fd;
    struct stat buf;
    struct timespec time[2];
    
    for (int i=1; i<argc; i++)
    {
        if (stat(argv[1], &buf) < 0)
            err_sys("stat error error for %s", argv[i]);

        if ((fd = open(argv[1], O_RDWR | O_TRUNC)) < 0)
        {
            err_ret("open error for %s", argv[i]);
            continue;
        }

        time[0]=buf.st_atim;
        time[1]=buf.st_mtim;
        if (futimens(fd, time) < 0)
            err_ret("futimens error for %s", argv[i]);

        close(fd);
    }

    return 0;
}
