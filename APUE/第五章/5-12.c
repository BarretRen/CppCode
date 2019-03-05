#include "../include/apue.h"

int main()
{
    char name[L_tmpnam];
    char line[MAXLINE];
    FILE* fp;

    printf("%s\n", tmpnam(NULL));

    tmpnam(name);
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL) //创建临时文件
        err_sys("tmpfile failed");

    fputs("one line for output\n", fp);//写内容到临时文件
    rewind(fp); //将文件指针移到开始处
    if (fgets(line, sizeof(line), fp) == NULL)
        err_sys("fgets error");

    printf("%s", line);
    return 0;
}
