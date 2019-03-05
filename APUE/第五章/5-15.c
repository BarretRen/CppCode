#include "../include/apue.h"

#define BSZ 48

int main()
{
    FILE* fp;
    char buf[BSZ];

    memset(buf, 'a', BSZ - 2);
    buf[BSZ -2] = '\0';
    buf[BSZ -1] = 'x';

    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL)
        err_sys("fmemopen failed");

    printf("inital buffer contents: %s\n", buf);//调用fmemopen后，buf被创建为内存流，之前内容被清空, 并在起始位置添加NULL字节
    fprintf(fp, "hello, world");
    printf("before fflush: %s\n", buf);
    fflush(fp);
    printf("after fflush:%s\n", buf);//在流冲洗后缓冲区才发生变化，新写入的字符串才能打印出来
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'b', BSZ - 2);
    buf[BSZ -2] = '\0';
    buf[BSZ -1] = 'x';
    fprintf(fp, "hello, world");//null字节当前在末尾，新写入的会被添加到末尾,并追加null字节
    printf("before fseek:%s\n", buf);
    fseek(fp, 0, SEEK_SET); //调用fseek后，缓冲区发送变化，新写入的可以打印
    printf("after fseek:%s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    memset(buf, 'c', BSZ - 2);
    buf[BSZ -2] = '\0';
    buf[BSZ -1] = 'x';
    fprintf(fp, "hello, world");//fseek指针当前在首部，写入在最前面，不会追加null字节，因为不能再首部加null
    printf("before fclose:%s\n", buf);
    fclose(fp);//缓冲区发送变化，新写入的可以打印
    printf("after fclose:%s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));
    return 0;
}
