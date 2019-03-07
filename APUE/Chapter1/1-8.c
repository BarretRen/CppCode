#include "../include/apue.h"
#include <errno.h>

int main(int argc, char* argv[])
{
    fprintf(stderr, "strerror return %s\n", strerror(EACCES));
    errno = ENOENT;
    perror(argv[0]);
    return 0;
}
