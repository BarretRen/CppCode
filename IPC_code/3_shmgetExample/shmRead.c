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
    shmid = shmget(1234, sizeof(STU), 0);//打开填0即可
    if (shmid == -1)
        ERR_EXIT("shmget faile");

    STU *p;
    p = (STU*)shmat(shmid, NULL, SHM_RND);//映射内存到进程的地址空间
    if (p == (void*)-1)
        ERR_EXIT("shmat failed");
    
    //读取内存中值
    printf("name:%s, age:%d", p->name, p->age);

    shmdt(p);//解除映射
    shmctl(shmid, IPC_RMID, NULL);//删除共享内存

    return 0;
}
