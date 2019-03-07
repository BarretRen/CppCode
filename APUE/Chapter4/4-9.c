#include "../include/apue.h"
#include <fcntl.h>

int main()
{
    //设置文件权限umaks
    mode_t old_mode = umask(0);
    printf("old mask is %d\n", old_mode);

    if (creat("foo.txt", 0666) < 0)
        err_sys("create error for foo");

    //更改umask
    old_mode = umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    printf("old mask is %d\n", old_mode);

    if (creat("bar.txt", 0666) < 0)
        err_sys("create error for bar");

    return 0;
}
