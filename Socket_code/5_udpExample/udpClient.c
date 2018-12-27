#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//指定server地址

    //send and receive data
    char sendbuf[1024] = {0};
    int ret;
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        sendto(sock, sendbuf, strlen(sendbuf), 0, (sockaddr*)&servaddr, sizeof(servaddr));
        memset(sendbuf, 0, sizeof(sendbuf));
        ret = recvfrom(sock, sendbuf, sizeof(sendbuf), 0, NULL, NULL);//从server接收，不需要指定ip
        if (ret == -1)
        {
            if (errno == EINTR)
                continue;//是系统中断导致，则继续
            ERR_EXIT("recvfrom failed");
        }
        else if (ret > 0)
        {
            printf("%s\r\n", sendbuf);
            memset(sendbuf, 0, sizeof(sendbuf));
        }
    }
    close(sock);
}
