#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

//创建信号量集
int sem_create(key_t key)
{
    int semid;
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid == -1)
        ERR_EXIT("semget create failed");
    return semid;
}
//打开一个已经存在的信号量集
int sem_open(key_t key)
{
    int semid;
    semid = semget(key, 0, 0);
    if (semid == -1)
        ERR_EXIT("get sem failed");

    return semid;
}

//设置当前计数值
int sem_setval(int semid, int val)
{
    union semun s;
    s.val = val;
    int ret = semctl(semid, 0, SETVAL, s);
    if (ret == -1)
        ERR_EXIT("semctl setval failed");

    return 0;
}

//获取当前计数值
int sem_getval(int semid)
{
    int ret = semctl(semid, 0, GETVAL, 0);
    if (ret == -1)
        ERR_EXIT("semctl getval failed");

    return ret;
}

//删除信号量集
int sem_d(int semid)
{
    if (semctl(semid, 0, IPC_RMID, 0) == -1)
        ERR_EXIT("semctl delete failed");

    return 0;
}

//PV操作
int sem_p(int semid)
{
    sembuf s = {0, -1, 0};
    int ret = semop(semid, &s, 1);
    if (ret == -1)
        ERR_EXIT("semop P failed");

    return ret;
}

int sem_v(int semid)
{
    sembuf s = {0, 1, 0};
    int ret = semop(semid, &s, 1);
    if (ret == -1)
        ERR_EXIT("semop V failed");

    return ret;
}

int main(int argc, char* argv[])
{
    int opt = getopt(argc, argv, "cdpvs:gfm");
    if (opt == '?')
        exit(EXIT_FAILURE);
    if (opt == -1)
    {
        exit(EXIT_FAILURE);
    }
    key_t key = ftok(".", 's');
    int semid;
    switch(opt)
    {
        case 'c':
            sem_create(key);
            break;
        case 'p':
            semid = sem_open(key);
            sem_p(semid);
            printf("current sem value: %d\r\n", sem_getval(semid));
            break;
        case 'v':
            semid = sem_open(key);
            sem_v(semid);
            printf("current sem value: %d\r\n", sem_getval(semid));
            break;
        case 'd':
            semid = sem_open(key);
            sem_d(semid);
            break;
        case 's':
            semid = sem_open(key);
            sem_setval(semid, atoi(optarg));
            break;
        case 'g':
            semid = sem_open(key);
            printf("current sem value: %d\r\n", sem_getval(semid));
            break;
    }
    return 0;
}
