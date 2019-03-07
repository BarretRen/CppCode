#include "../include/apue.h"

int main()
{
    char* p;
    size_t size;

    if(chdir("/home/barretr/binary") < 0)
        err_sys("chdir failed");

    p = path_alloc(&size);
    if(getcwd(p, size) == NULL)
        err_sys("getcwd failed");

    printf("cwd=%s", p);

    return 0;
}
