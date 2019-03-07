#include "../include/apue.h"
#include <errno.h>

void make_temp(char* temp)
{
    int fd;
    struct stat buf;
    
    if ((fd = mkstemp(temp)) < 0)
        err_sys("cannot create temp file");

    printf("temp name = %s\n", temp);
    close(fd);

    if (stat(temp, &buf) < 0)
    {
        if (errno == ENOENT)
            printf("file does not exist]n");
        else
            err_sys("stat failed");
    }
    else
    {
        printf("file exists\n");
        unlink(temp);
    }
}


int main()
{
    char good_tmp[]="/tmp/dirXXXXXX";
    char *bad_tmp="/tmp/dirXXXXXX";

    printf("trying to create the first temp file...\n");
    make_temp(good_tmp);
    printf("trying to create the second temp file...\n");
    make_temp(bad_tmp);

    return 0;
}
