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

//创建信号量集: 5把刀叉
int sem_create(key_t key)
{
    int semid;
    semid = semget(key, 5, IPC_CREAT | IPC_EXCL | 0666);
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

//设置当前计数值, index为信号量集中信号量的索引
int sem_setval(int semid, int index, int val)
{
    union semun s;
    s.val = val;
    int ret = semctl(semid, index, SETVAL, s);
    if (ret == -1)
        ERR_EXIT("semctl setval failed");

    return 0;
}

//获取当前计数值
int sem_getval(int semid, int index)
{
    int ret = semctl(semid, index, GETVAL, 0);
    if (ret == -1)
        ERR_EXIT("semctl getval failed");

    return ret;
}

//删除信号量集
int sem_d(int semid, int index)
{
    if (semctl(semid, index, IPC_RMID, 0) == -1)
        ERR_EXIT("semctl delete failed");

    return 0;
}

//PV操作,同时操作两个信号量
int sem_p(int semid, int left, int right)
{
    sembuf s[2] = {
        {left, -1, 0}, 
        {right, -1, 0}
    };
    int ret = semop(semid, s, 2);
    if (ret == -1)
        ERR_EXIT("semop P failed");

    return ret;
}

int sem_v(int semid, int left, int right)
{
    sembuf s[2] = {
        {left, 1, 0}, 
        {right, 1, 0}
    };
    int ret = semop(semid, s, 2);
    if (ret == -1)
        ERR_EXIT("semop V failed");

    return ret;
}

void waitFor2Chazi(int semid, int num)
{
    //计算左右两边叉子的编号
    int left = num;
    int right = (num + 1) % 5;
    sem_p(semid, left, right);
}

void free2Chazi(int semid, int num)
{
    //计算左右两边叉子的编号
    int left = num;
    int right = (num + 1) % 5;
    sem_v(semid, left, right);
}

void HandleChazi(int semid, int num)
{
    srand(getpid());
    for(;;)
    {
        printf("%d is thinking\r\n", num);
        sleep(rand() % 5 + 1);
        printf("%d is hungry\r\n", num);
        //等待获取两把叉子
        waitFor2Chazi(semid, num);
        printf("%d is eating\r\n", num);
        sleep(rand() % 5 + 1);
        free2Chazi(semid, num);
        printf("%d stop eating\r\n", num);
    }
}


int main(int argc, char* argv[])
{
    int semid;
    semid = sem_create(IPC_PRIVATE);

    for (int i=0; i<5; i++)
    {
        sem_setval(semid, i, 1);
    }

    //创建4个子进程，模拟5个吃饭的人
    pid_t pid;
    int num = 0;
    for(int i=1; i<5; i++)
    {
        pid = fork();
        if (pid == -1)
            ERR_EXIT("fork");
        if(pid == 0)
        {
            //子进程
            num = i;//主进程num为0，子进程num依次为1,2,3,4
            break;
        }
    }

    HandleChazi(semid, num);
    return 0;
}
