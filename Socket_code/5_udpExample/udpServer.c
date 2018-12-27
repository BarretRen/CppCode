#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

int main()
{
    int sock;
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)//类型指定为数据报式，用于TCP
    {
        ERR_EXIT("socket create failed"); 
    }

    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind the socket
    if (bind(sock, (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        ERR_EXIT("bind socket failed");
    }

    //send and receive data
    char recvbuf[1024] = {0};
    sockaddr_in remoteAddr;
    socklen_t remoteLen = sizeof(remoteAddr);
    int ret;
    while (1)
    {
        memset(recvbuf, 0, sizeof(recvbuf));
        ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, (sockaddr*)&remoteAddr, &remoteLen);
        if (ret == -1)
        {
            if (errno == EINTR)
                continue;//是系统中断导致，则继续
            ERR_EXIT("recvfrom failed");
        }
        else if (ret > 0)
        {
            printf("%s\r\n", recvbuf);
            sendto(sock, recvbuf, ret, 0, (sockaddr*)&remoteAddr, remoteLen);
        }
    }
    close(sock);
}
