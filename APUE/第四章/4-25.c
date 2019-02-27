#include "../include/apue.h"

int main(int argc, char* argv[])
{
    struct stat buf;

    for (int i=0; i< argc; i++)
    {
        printf("%s: ", argv[i]);
        if (stat(argv[1], &buf) < 0)
        {
            err_ret("stat error");
            continue;
        }

        printf("dev=%d/%d", gnu_dev_major(buf.st_dev), gnu_dev_minor(buf.st_dev));
        if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
        {
            printf("%s rdev = %d/%d", (S_ISCHR(buf.st_mode)) ? "Character" : "block", gnu_dev_major(buf.st_dev), gnu_dev_minor(buf.st_dev));
        }
        printf("\n");
    }
    return 0;
}
