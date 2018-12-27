#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include "types.h"

//当前用户名
User_List client_list;

void handleClientEvent(int sock)
{
    sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//指定server地址
    int ret;
    message msg;
    char username[16];
    while (1)
    {
        memset(username, 0, sizeof(username));
        printf("please input your username: ");
        scanf("%s", username);

        memset(&msg, 0, sizeof(msg));
        msg.msgType = htonl(C2S_LOGIN);
        strcpy(msg.msgBody, username);
        sendto(sock, &msg, sizeof(msg), 0, (sockaddr*)&servaddr, sizeof(servaddr));

        memset(&msg, 0, sizeof(msg));
        recvfrom(sock, &msg, sizeof(msg), 0, NULL,NULL);
        chatTypes type = (chatTypes)htonl(msg.msgType);
        printf("receive msg type:%d\r\n", type);
        if (type == S2C_ALREADY_LOGINED)
        {
            printf("user %s already logined server, please use another username\r\n", username);
        }
        else if (type == S2C_LOGIN_OK)
        {
            printf("user %s has logined server\r\n", username);
            break; //登录成功，跳出循环
        }
    }
    
    int count;
    recvfrom(sock, &count, sizeof(int), 0, NULL, NULL);
    int n = htonl(count);
    printf("has %d users logined in server\r\n", n);

    user_info user;
    in_addr tmp;
    for (int i=0; i<n; i++)
    {
        recvfrom(sock, &user, sizeof(user_info), 0, NULL, NULL);
        client_list.push_back(user);
        tmp.s_addr = user.ip;
        printf("%d %s <-> %s:%d\r\n", i, user.username, inet_ntoa(tmp), ntohs(user.port));
    }

    printf("\nCommands are:\n");
    printf("send <username> msg\n");
    printf("list\nexit\n\n");

    close(sock);
}

int main()
{
    int sock;
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)//类型指定为数据报式，用于TCP
    {
        ERR_EXIT("socket create failed"); 
    }


    handleClientEvent(sock);
    return 0;
}
