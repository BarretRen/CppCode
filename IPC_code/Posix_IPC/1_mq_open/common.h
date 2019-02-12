#ifndef _COMMON_H
#define _COMMON_H
#include <errno.h>

#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

#endif
