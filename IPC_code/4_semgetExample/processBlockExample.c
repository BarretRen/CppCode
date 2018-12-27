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
#include <sys/wait.h>


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

void handlePrint(int semid, char c)
{
    int pause_time;
    srand(getpid());
    for (int i=0; i<10; i++)
    {
        sem_p(semid);
        printf("%c", c);
        fflush(stdout);
        pause_time = rand() % 3;
        sleep(pause_time);
        sem_v(semid);
    }
}

int main(int argc, char* argv[])
{
    int semid;
    semid = sem_create(IPC_PRIVATE);
    sem_setval(semid, 0);

    pid_t pid = fork();
    if (pid == -1)
        ERR_EXIT("fork failed");

    if (pid > 0)
    {
        //父进程，打印输出O
        sem_setval(semid, 1);
        handlePrint(semid, 'O');
        //父进程等待子进程退出后，删除信号量
        wait(NULL);
        sem_d(semid);
    }
    else if (pid == 0)
    {
        //子进程，打印输出X
        handlePrint(semid, 'X');
    }
    return 0;
}
