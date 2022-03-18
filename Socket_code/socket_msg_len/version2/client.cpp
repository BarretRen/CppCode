#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include "utils.h"
#include <iostream>
using namespace std;

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

    //echo 回射client端发送与接收代码
    struct Packet buf;
    memset(&buf, 0, sizeof(buf));
    int oltSize = sizeof(struct T_LogicalIndex);
    while (fgets(buf.text, sizeof(buf.text), stdin) != NULL)
    {
        /**写入部分**/
        buf.oltIndex.ifType = htons(2);
        buf.oltIndex.slot = htons(10);
        buf.oltIndex.logical = htons(11);
        buf.oltIndex.powerLevel = htons(100);
        buf.oltIndex.temperature = htons(40);
        buf.oltIndex.voltage = htons(20);
        buf.oltIndex.biasCurrent = htons(5);

        unsigned int lenHost = strlen(buf.text) + oltSize;
        buf.msgLen = htonl(lenHost);
        if (writen(socketId, &buf, sizeof(buf.msgLen) + lenHost) == -1)
            err_exit("writen socket error");

        /**读取部分**/
        memset(&buf, 0, sizeof(buf));
        //首先读取首部
        ssize_t readBytes = readn(socketId, &buf.msgLen, sizeof(buf.msgLen));
        if (readBytes == -1)
            err_exit("read socket error");
        else if (readBytes != sizeof(buf.msgLen))
        {
            cerr << "server connect closed... \nexiting..." << endl;
            break;
        }

        //然后读取数据部分
        lenHost = ntohl(buf.msgLen) - oltSize;
        readBytes = readn(socketId, (&(buf.oltIndex.ifType)), oltSize);
        if (readBytes == -1)
            err_exit("read socket error");
        else if (readBytes != oltSize)
        {
            cerr << "server connect closed... \nexiting..." << endl;
            break;
        }

        readBytes = readn(socketId, buf.text, lenHost);  
        if (readBytes == -1)  
            err_exit("read socket error");  
        else if (readBytes != lenHost)  
        {  
            cerr << "server connect closed... \nexiting..." << endl;  
            break;  
        }  

        //将数据部分打印输出
        cout << "returned from server: "<<buf.text<<endl;
        cout <<ntohs(buf.oltIndex.ifType) <<"\t"
            <<ntohs(buf.oltIndex.slot)<<"\t"
            <<ntohs(buf.oltIndex.logical)<<"\t"
            <<ntohs(buf.oltIndex.powerLevel)<<"\t"
            <<ntohs(buf.oltIndex.temperature)<<"\t"
            <<ntohs(buf.oltIndex.voltage)<<"\t"
            <<ntohs(buf.oltIndex.biasCurrent)<<endl;

        memset(&buf, 0, sizeof(buf));
    }

    close(socketId);
    return 0;
}
