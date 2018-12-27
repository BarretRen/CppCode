#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct student
{
    char name[4];
    int age;
}STU;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s, <filename>\r\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd;
    fd = open(argv[1], O_RDWR, 0666); //打开文件
    if (fd == 1)
        ERR_EXIT("open failed");

    STU* p = (STU*)mmap(NULL, sizeof(STU) * 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);//将文件映射为共享内存
    if (p == NULL)
        ERR_EXIT("mmap failed");

    char ch = 'a';
    for (int i = 0; i < 5; i++)
    {
        printf("name = %s, age = %d\r\n", (p+i)->name, (p+i)->age);
    }

    munmap(p, sizeof(STU) * 5);
    printf("exit\r\n");

    return 0;
}
