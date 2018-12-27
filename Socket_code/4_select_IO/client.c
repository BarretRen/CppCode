#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{
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
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //connect to server via socket
    if (connect(socketId, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        printf("connect to server failed\r\n");
    }

    //使用select实现IO复用模式读写数据
    fd_set rset;
    FD_ZERO(&rset);//create a set and initial it
    int stdinFd = fileno(stdin); //获取标准输入的文件描述符
    int maxfd = (stdinFd < socketId) ? socketId : stdinFd;
    int nready;
    char recvbuf[1024];
    char sendbuf[1024];

    while(1)
    {
        FD_SET(stdinFd, &rset);
        FD_SET(socketId, &rset);
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);    
        if (nready == -1)
            printf("select failed\r\n");
        else if (nready == 0)
            continue;
        else
        {
            //产生可读事件，返回的是那个fd产生的
            //检查是那个fd产生的事件
            if (FD_ISSET(socketId, &rset))
            {
                //是socket产生可读事件，表示数据到来，获取数据
                read(socketId, recvbuf, sizeof(recvbuf));
                printf("received from server: %s\r\n", recvbuf);
                memset(recvbuf, 0, sizeof(recvbuf));
            }
            else if (FD_ISSET(stdinFd, &rset))
            {
                //是控制台输入产生的可读事件，表示用户输入数据了，需要发送到server
                if (fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)
                    break;
                write(socketId, sendbuf, strlen(sendbuf));
                memset(sendbuf, 0, sizeof(sendbuf));
            }
        }
    }
    close(socketId);
    return 0;
}
