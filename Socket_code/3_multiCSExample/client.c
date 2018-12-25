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
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //connect to server via socket
    if (connect(socketId, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        printf("connect to server failed\r\n");
    }

    char buf[1024];
    while (fgets(buf, sizeof(buf), stdin) != NULL)
    {
        write(socketId, buf, strlen(buf));
        read(socketId, buf, sizeof(buf));//read reply from server

        printf("received from server: %s\r\n", buf);
        memset(buf, 0, sizeof(buf));
    }

    close(socketId);
    return 0;
}
