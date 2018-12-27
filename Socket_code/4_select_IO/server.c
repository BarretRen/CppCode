#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <errno.h>

void customHandler(int sig)
{
    while(waitpid(-1, NULL, WNOHANG) > 0)
        ;
}
int main()
{
    //add SIGCHLD signal handler
    signal(SIGCHLD, customHandler);
    //create socket
    int socketId;
    if ((socketId = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("socket create failed\r\n");
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET; //指定协议
    addr.sin_port = htons(5188); //指定网络字节序格式的端口号
    /** addr.sin_addr = htonl(INADDR_ANY); //指定本地任意ip地址，使用网络字节序 */
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //set REUSEADDR
    int on = 1;
    if(setsockopt(socketId, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        printf("socket set REUSEADDR failed\r\n");
    }
    //start bind
    if (bind(socketId, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        printf("socket bind failed\r\n");
    }
    //start listen
    if (listen(socketId, SOMAXCONN) < 0)
    {
        printf("socket listen failed\r\n");
    }

    sockaddr_in remoteAddr;
    socklen_t remoteLen = sizeof(remoteAddr);
    int remoteConnId;

    //select IO复用方式实现多客户端连接处理
    int connectedClient[FD_SETSIZE];//最大值为select函数可接受的最多fd
    for (int i = 0; i < FD_SETSIZE; i++)
    {
        connectedClient[i] = -1;
    }
    int nready;
    int maxFd = socketId;
    fd_set rset;
    fd_set allset;
    FD_ZERO(&rset);
    FD_ZERO(&allset);
    FD_SET(socketId, &allset);//第一次添加监听socket，此时还没有客户端socket

    while(1)
    {
        rset = allset;
        nready = select(maxFd + 1, &rset, NULL, NULL, NULL);
        if (nready == -1)
        {
            //select失败，判断是否为系统中断导致，是中断则继续
            if (errno == EINTR)
                continue;
            printf("select failed");
            return 0;
        }
        else if (nready == 0)
            continue;

        if (FD_ISSET(socketId, &rset))
        {
            //监听端口有可读事件，表示有客户端连接过来，需要建立连接
            remoteConnId = accept(socketId, (sockaddr*)&remoteAddr, &remoteLen);
            if (remoteConnId == -1)
            {
                printf("accept failed");
                return 0;
            }
            int i;
            for (int i = 0; i < FD_SETSIZE; i++)
            {
                if (connectedClient[i] == -1)
                {
                    connectedClient[i] = remoteConnId;
                    break;
                }
            }
            if (i == FD_SETSIZE)
            {
                printf("too many clients");
                return 0;
            }

            printf("IP = %s, port = %d\r\n", inet_ntoa(remoteAddr.sin_addr), ntohs(remoteAddr.sin_port));
            FD_SET(remoteConnId, &allset);//添加已连接的socket到下一次select集合中
            if (remoteConnId > maxFd) //更新最大fd值
                maxFd = remoteConnId;
            if (--nready <= 0)
                continue; //返回集合都处理了，继续下一次循环
        }
        //处理已连接socket的读写事件
        for (int i = 0; i < FD_SETSIZE; i++)
        {
            remoteConnId = connectedClient[i];
            if (remoteConnId == -1)
                continue;
            if (FD_ISSET(remoteConnId, &rset))
            {
                char rcvBuf[1024] = {0};
                int ret = read(remoteConnId, rcvBuf, sizeof(rcvBuf));// 从socket中读取数据流
                if (ret == 0)
                {
                    printf("close client: [%d]\r\n", remoteConnId);
                    connectedClient[i] = -1;
                    FD_CLR(remoteConnId, &allset);
                    close(remoteConnId);
                }
                fputs(rcvBuf, stdout);
                write(remoteConnId, rcvBuf, strlen(rcvBuf));//将数据再写回remote端
                
                if (--nready <= 0)
                    continue;
            }
        }
    }

    close(socketId);
    return 0;
}
