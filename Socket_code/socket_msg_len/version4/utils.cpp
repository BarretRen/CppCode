#include "utils.h"
#include <stdio.h>		/* for convenience */
#include <stdlib.h>		/* for convenience */
#include <stddef.h>		/* for offsetof */
#include <string.h>		/* for convenience */
#include <unistd.h>		/* for convenience */
#include <signal.h>		/* for SIG_ERR */
#include <errno.h>
#include <sys/types.h>		/* some systems still require this */
#include <sys/stat.h>
#include <sys/ioctl.h>


/* Write "n" bytes to a descriptor  */
ssize_t writen(int fd, const char *ptr, size_t n)
{
    size_t		nleft;
    ssize_t		nwritten;

    nleft = n;
    while (nleft > 0) {
        if ((nwritten = write(fd, ptr, nleft)) < 0) {
            if (EINTR == errno)
                return(-1); /* error, return -1 */
            else
                break;      /* error, return amount written so far */
        } else if (nwritten == 0) {
            break;
        }
        nleft -= nwritten;
        ptr   += nwritten;
    }
    return(n - nleft);      /* return >= 0 */
}

/* Read "n" bytes from a descriptor  */
ssize_t readn(int fd, char *ptr, size_t n)
{
    size_t		nleft;
    ssize_t		nread;

    nleft = n;
    while (nleft > 0) {
        if ((nread = read(fd, ptr, nleft)) < 0) {
            if (EINTR == errno)
                return(-1); /* error, return -1 */
            else
                break;      /* error, return amount read so far */
        } else if (nread == 0) {
            break;          /* EOF */
        }
        nleft -= nread;
        ptr   += nread;
    }
    return(n - nleft);      /* return >= 0 */
}

