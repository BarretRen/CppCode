#include "../include/apue.h"

int main(int argc, char* argv[])
{
    char** p;
    extern char** environ;

    for (int i=0; i<argc; i++)
        printf("argv[%d]: %s\n", i, argv[i]);

    for (p = environ; *p != 0; p++)
        printf("%s\n", *p);//打印环境表
    return 0;
}
