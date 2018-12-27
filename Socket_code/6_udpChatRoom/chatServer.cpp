#include "types.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

//global variable
User_List client_list;

void do_login(message& msg, int sock, sockaddr_in* clientaddr);
void do_logout(message& msg, int sock, sockaddr_in* clientaddr);
void do_sendlist(int sock, sockaddr_in* clientaddr);
void handleServerEvent(int sock);

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

    handleServerEvent(sock);
    return 0;
}

void handleServerEvent(int sock)
{
    //send and receive data
    sockaddr_in remoteAddr;
    socklen_t remoteLen = sizeof(remoteAddr);
    int ret;
    message msg;
    while (1)
    {
        memset(&msg, 0, sizeof(msg));
        ret = recvfrom(sock, &msg, sizeof(msg), 0, (sockaddr*)&remoteAddr, &remoteLen);
        if (ret == -1)
        {
            if (errno == EINTR)
                continue;//是系统中断导致，则继续
            ERR_EXIT("recvfrom failed");
        }
        //chec the message type
        chatTypes type = (chatTypes)ntohl(msg.msgType);
        printf("receive msg type:%d\r\n", type);
        switch(type)
        {
            case C2S_LOGIN:
                do_login(msg, sock, &remoteAddr);
                break;
            case C2S_LOGOUT:
                do_logout(msg, sock, &remoteAddr);
                break;
            case C2S_ONLINE_USER:
                do_sendlist(sock, &remoteAddr);
                break;
            default:
                break;
        }
    }
    close(sock);
}

void do_login(message& msg, int sock, sockaddr_in* clientaddr)
{
    user_info user;
    strcpy(user.username, msg.msgBody);//讲msg中携带的用户名复制到user_info
    user.ip = clientaddr->sin_addr.s_addr;
    user.port = clientaddr->sin_port;
    //查找用户是否存在
    User_List::iterator it;
    for (it = client_list.begin(); it != client_list.end();it++)
    {
        if (strcmp(it->username, user.username) == 0)
        {
            break;
        }
    }
    
    if (it == client_list.end())
    {
        in_addr tmp;
        tmp.s_addr = user.ip;
        printf("has a new user login: %s <-> %s:%d\r\n", user.username, inet_ntoa(tmp), user.port);
        client_list.push_back(user);
        //登录成功，回复刚才登录的client
        message reply;
        reply.msgType = htonl(S2C_LOGIN_OK);
        if(sendto(sock, &reply, sizeof(reply), 0, (sockaddr*)clientaddr, sizeof(*clientaddr)) < 0)
            ERR_EXIT("sendto failed");
        //发送在线人数到刚登录的client
        int count = htonl((int)client_list.size());
        if(sendto(sock, &count, sizeof(int), 0, (sockaddr*)clientaddr, sizeof(*clientaddr)) < 0)
            ERR_EXIT("sendto failed");
        //发送当前登录用户列表
        //通知其他client有新用户登录
        sockaddr_in remoteAddr;
        for (it = client_list.begin(); it != client_list.end();it++)
        {
            sendto(sock, &*it, sizeof(user_info), 0, (sockaddr*)clientaddr, sizeof(*clientaddr));

            if (strcmp(it->username, user.username) == 0)
                continue;

            memset(&remoteAddr, 0, sizeof(remoteAddr));
            remoteAddr.sin_family = AF_INET;
            remoteAddr.sin_port = it->port;
            remoteAddr.sin_addr.s_addr = it->ip;

            msg.msgType = htonl(S2C_SOMEONE_LOGIN);
            memcpy(msg.msgBody, &user, sizeof(user_info));

            if (sendto(sock, &msg, sizeof(msg), 0, (sockaddr*)&remoteAddr, sizeof(remoteAddr)) < 0)
                ERR_EXIT("sendto failed");
        }
    }
    else
    {
        //用户已经登录过
        printf("user %s has already logined\r\n", user.username);
        message reply;
        reply.msgType = htonl(S2C_ALREADY_LOGINED);
        if(sendto(sock, &reply, sizeof(reply), 0, (sockaddr*)clientaddr, sizeof(*clientaddr)) < 0)
            ERR_EXIT("sendto failed");
    }
}

void do_logout(message& msg, int sock, sockaddr_in* clientaddr)
{

}

void do_sendlist(int sock, sockaddr_in* clientaddr)
{

}
