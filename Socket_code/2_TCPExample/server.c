#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

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

    //get connection from socket queue
    sockaddr remoteAddr;
    socklen_t remoteLen = sizeof(remoteAddr);
    int remoteConnId;
    if ((remoteConnId = accept(socketId, (sockaddr*)&remoteAddr, &remoteLen)) < 0)
    {
        printf("socket accept failed\r\n");
    }

    char rcvBuf[1024];
    while(1)
    {
        memset(rcvBuf, 0, sizeof(rcvBuf));
        read(remoteConnId, rcvBuf, sizeof(rcvBuf));// 从socket中读取数据流
        printf("%s\r\n", rcvBuf);
        write(remoteConnId, rcvBuf, strlen(rcvBuf));//将数据再写回remote端
    }
    
    close(remoteConnId);
    close(socketId);
    return 0;
}
