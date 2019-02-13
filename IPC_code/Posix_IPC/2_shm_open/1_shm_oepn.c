#include "common.h"
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */


struct student
{
    char name[32];
    int age;
};

int main()
{
    //创建共享内存
    int shmid = shm_open("/xyz", O_CREAT | O_RDWR, 0666);
    if (shmid == -1)
        ERR_EXIT("shm_open failed");
    //设置共享内存大小
    if (ftruncate(shmid, sizeof(student)) == -1)
        ERR_EXIT("ftruncate failed");

    struct stat buf;
    //获取共享内存信息
    if (fstat(shmid, &buf) == -1)
        ERR_EXIT("fstat failed");

    printf("size=%d, mode=%d\r\n", buf.st_size, buf.st_mode & 0777);

    //映射共享内存到进程地址空间
    student* p = (student*)mmap(NULL, buf.st_size, PROT_WRITE, MAP_SHARED, shmid, 0);
    if (p == MAP_FAILED)
        ERR_EXIT("mmap failed");

    strcpy(p->name, "test");
    p->age = 29;

    if (shm_unlink("/xyz") == -1)
        ERR_EXIT("shm_unlink");

    return 0;
}
