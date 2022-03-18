#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include <iostream>
using namespace std;

//server端echo部分的改进代码
void echo(int clientfd)
{
    struct Packet buf;
    int readBytes = 0;
    int oltSize = sizeof(struct T_LogicalIndex)*2;
    char text[1024]={0};
    struct T_LogicalIndex oltIndex[2]={0};
    //首先读取首部
    while ((readBytes = readn(clientfd, (char*)&buf, sizeof(buf))) > 0)
    {
        //网络字节序 -> 主机字节序
        int lenHost = ntohl(buf.msgLen) - oltSize;
        //然后读取数据部分
        readBytes = readn(clientfd, (char*)&oltIndex, oltSize);
        if (readBytes == -1)
            err_exit("read socket error");
        else if (readBytes != oltSize)
        {
            cerr << "server connect closed... \nexiting..." << endl;
            break;
        }

        readBytes = readn(clientfd, text, lenHost);  
        if (readBytes == -1)  
            err_exit("read socket error");  
        else if (readBytes != lenHost)  
        {  
            cerr << "server connect closed... \nexiting..." << endl;  
            break;  
        }  

        cout<<"msgType:"<<ntohl(buf.msgType)<<endl;
        cout<<text<<endl;
        for(int i=0;i<2;i++)
        {
            cout <<ntohs(oltIndex[i].ifType) <<"\t"
                <<ntohs(oltIndex[i].slot)<<"\t"
                <<ntohs(oltIndex[i].logical)<<"\t"
                <<ntohs(oltIndex[i].powerLevel)<<"\t"
                <<ntohs(oltIndex[i].temperature)<<"\t"
                <<ntohs(oltIndex[i].voltage)<<"\t"
                <<ntohs(oltIndex[i].biasCurrent)<<endl;
        }

        char* tmp = new char[sizeof(buf)+lenHost+oltSize];
        //fill in the char array
        memcpy(tmp, &buf, sizeof(buf));
        memcpy(tmp + sizeof(buf), &oltIndex, oltSize);
        memcpy(tmp + sizeof(buf) + oltSize, text, strlen(text));

        //然后将其回写回socket
        if (writen(clientfd, tmp, sizeof(buf)+lenHost+oltSize) == -1)
            err_exit("write socket error");

        memset(&buf, 0, sizeof(buf));
        memset(&oltIndex, 0, oltSize);
        memset(text, 0, 1024);
    }
    if (readBytes == -1)
    {
        err_exit("read socket error");
        close(clientfd);
    }
    else if (readBytes != sizeof(buf.msgLen))
    {
        cerr << "client connect closed..." << endl;
        close(clientfd);
    }
}

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
    /** addr.sin_addr = htonl(INADDR_ANY); //指定本地任意ip地址，使用网络字节序 */
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

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

    //get connection from socket queue
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
            echo(remoteConnId);
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
