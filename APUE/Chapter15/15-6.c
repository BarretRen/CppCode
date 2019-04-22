#include "../include/apue.h"
#include <sys/wait.h>

#define DEF_PAGER "/bin/more" //默认的分页程序

int main(int argc, char* argv[])
{
    int n;
    int fd[2];//管道标识符
    pid_t pid;
    char *pager, *argv0;
    char line[MAXLINE];
    FILE *fp;

    if (argc !=2)
        err_quit("usage: a.out <pathname>");

    if ((fp = fopen(argv[1], "r")) == NULL)
        err_sys("cannot open %s", argv[1]);

    if (pipe(fd) < 0)
        err_sys("pipe error");

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid > 0)
    {
        //父进程
        close(fd[0]); //关闭读端
        //将文件内容写入pipe
        while (fgets(line, MAXLINE, fp) != NULL)
        {
            n = strlen(line);
            if (write(fd[1], line, n) != n)
                err_sys("write error to pipe");
        }
        if (ferror(fp))
            err_sys("fgets error");
        close(fd[1]);//关闭写端
        
        if (waitpid(pid, NULL, 0) < 0)
            err_sys("waitpid error");
        exit(0);
    }
    else
    {
        //子进程
        close(fd[1]);//关闭写端
        if (fd[0] != STDIN_FILENO)
        {
            //将pipe的读端映射到标准输入
            if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
                err_sys("dup2 error to stdin");
            close(fd[0]);
        }
        if ((pager = getenv("PAGER")) == NULL)
            pager = DEF_PAGER;

        //分页程序从标准输入获取内容，进行分页
        if ((argv0 = strchr(pager, '/')) != NULL)
            argv0++;
        else
            argv0 = pager;

        if (execl(pager, argv0, (char*)0) < 0)
            err_sys("excel error for %s", pager);
    }
    return 0;
}
