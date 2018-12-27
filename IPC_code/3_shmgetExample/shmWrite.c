#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>


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
    int shmid;
    shmid = shmget(1234, sizeof(STU), IPC_CREAT| 0666);
    if (shmid == -1)
        ERR_EXIT("shmget faile");

    STU *p;
    p = (STU*)shmat(shmid, NULL, SHM_RND);//映射内存到进程的地址空间
    if (p == (void*)-1)
        ERR_EXIT("shmat failed");

    strcpy(p->name, "barr");//直接对共享内存进行操作
    p->age = 20;

    shmdt(p);//解除映射

    return 0;
}
