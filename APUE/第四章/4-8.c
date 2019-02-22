#include "../include/apue.h"
#include <fcntl.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
        err_quit("usage: a.out <pathname>");

    if (access(argv[1], R_OK) < 0) //检查实际用户ID是否有读权限, 即当前执行文件所属的用户，不是执行该文件的用户
        err_ret("access error for %s with real user", argv[1]);
    else
        printf("read access OK\n");

    if(open(argv[1], O_RDONLY) < 0)
        err_ret("open error dor %s", argv[1]);
    else
        printf("open for reading OK");

    return 0;
}
