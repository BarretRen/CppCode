#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

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

    sockaddr remoteAddr;
    socklen_t remoteLen = sizeof(remoteAddr);
    int remoteConnId;

    pid_t pid;
    while (1)
    {
        //get connection from socket queue
        if ((remoteConnId = accept(socketId, (sockaddr*)&remoteAddr, &remoteLen)) < 0)
        {
            printf("socket accept failed\r\n");
            break;
        }
        
        pid = fork(); //创建新进程处理socket连接
        if (pid == -1)
        {
            printf("create new process failed\r\n");
            break;
        }
        if (pid == 0)
        {
            //子进程不需要处理socket监听，关闭监听
            close(socketId);
            //子进程处理connection
            char rcvBuf[1024];
            while(1)
            {
                memset(rcvBuf, 0, sizeof(rcvBuf));
                int ret = read(remoteConnId, rcvBuf, sizeof(rcvBuf));// 从socket中读取数据流
                if (ret == 0)
                {
                    printf("close client: [%d]\r\n", remoteConnId);
                    break;
                }
                fputs(rcvBuf, stdout);
                write(remoteConnId, rcvBuf, strlen(rcvBuf));//将数据再写回remote端
            }
            close(remoteConnId);
            //退出子进程
            _exit(0);
        }
        else
        {
            //父进程不需要处理socket连接，关闭connection
            close(remoteConnId);
        }
    }
    close(socketId);
    return 0;
}
