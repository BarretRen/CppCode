#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    time_t t;
    struct tm* tmp;
    char buf1[16];
    char buf2[64];

    time(&t);//获取秒数
    tmp = localtime(&t);//根据秒数得到tm结构体数据

    //打印tm时间为格式化字符串到buf,然后输出
    if(strftime(buf1, 16, "time and date: %r, %a %b %d, %Y", tmp) == 0)
        printf("buffer length 16 is too small\n");
    else
        printf("%s\n", buf1);
    
    if(strftime(buf2, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0)
        printf("buffer length 64 is too small\n");
    else
        printf("%s\n", buf2);

    return 0;
}
