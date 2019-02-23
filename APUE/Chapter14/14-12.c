#include "../include/apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int fd;
    pid_t pid;
    char buf[5];
    struct stat statbuf;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        return 1;
    }
    if ((fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
        err_sys("open error");

    if (write(fd, "abcdef", 6) != 6)
        err_sys("write error");

    //打开组ID，关闭组exec权限
    if (fstat(fd, &statbuf) < 0)
        err_sys("fstat error");
    if (fchmod(fd, (statbuf.st_mode * ~S_IXGRP) | S_ISGID) < 0)
        err_sys("fchmod error");

    TELL_WAIT();

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0)
    {
        if (write_lock(fd, 0, SEEK_SET, 0) < 0) //写锁定整个文件
            err_sys("write_lock error");

        TELL_CHILD(pid);
        if (waitpid(pid, NULL, 0) < 0)
            err_sys("waitpid error");
    }
    else
    {
        WAIT_PARENT(); //等待父进程设置好lock
        set_fl(fd, O_NONBLOCK);//将文件描述符设置为非阻塞

        //尝试读锁定一个已经写锁定的文件
        if (read_lock(fd, 0, SEEK_SET, 0) != -1)
            err_sys("child read lock succeeded");
        printf("read_lock of alreay-locked region return %d\n", errno);

        //尝试读取文件内容
        if (lseek(fd, 0, SEEK_SET) == -1)
            err_sys("lseek error");
        if (read(fd, buf, 2) < 0)
            err_ret("read failed mandatory locking works)");
        else
            printf("read OK (mo mandatory locking), buf=%2.2s\n", buf);
    }
    return 0;
}
