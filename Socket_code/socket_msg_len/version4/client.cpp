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
    int oltSize = sizeof(struct T_LogicalIndex)*2;
    char text[1024]={0};
    struct T_LogicalIndex oltIndex[2]={0};
    while (fgets(text, 1024, stdin) != NULL)
    {
        /**写入部分**/
        for(int i=0;i<2;i++)
        {
            oltIndex[i].ifType = htons(2+i);
            oltIndex[i].slot = htons(10+i);
            oltIndex[i].logical = htons(11+i);
            oltIndex[i].powerLevel = htons(100+i);
            oltIndex[i].temperature = htons(40+i);
            oltIndex[i].voltage = htons(20+i);
            oltIndex[i].biasCurrent = htons(5+i);
        }
        buf.msgType=htonl(10);

        unsigned int lenHost = strlen(text) + oltSize;
        buf.msgLen = htonl(lenHost);
        int lenMsg = sizeof(buf) + lenHost;
        char* tmp = new char[lenMsg];
        //fill in the char array
        memcpy(tmp, &buf, sizeof(buf));
        memcpy(tmp + sizeof(buf), &oltIndex, oltSize);
        memcpy(tmp + sizeof(buf) + oltSize, text, strlen(text));

        if (writen(socketId, tmp, lenMsg) == -1)
            err_exit("writen socket error");

        /**读取部分**/
        memset(&buf, 0, sizeof(buf));
        memset(&oltIndex, 0, oltSize);
        memset(text, 0, 1024);
        //首先读取首部
        ssize_t readBytes = readn(socketId, (char*)&buf, sizeof(buf));
        if (readBytes == -1)
            err_exit("read socket error");
        else if (readBytes != sizeof(buf))
        {
            cerr << "server connect closed... \nexiting..." << endl;
            break;
        }

        //然后读取数据部分
        lenHost = ntohl(buf.msgLen) - oltSize;
        readBytes = readn(socketId, (char*)&oltIndex, oltSize);
        if (readBytes == -1)
            err_exit("read socket error");
        else if (readBytes != oltSize)
        {
            cerr << "server connect closed... \nexiting..." << endl;
            break;
        }

        readBytes = readn(socketId, text, lenHost);  
        if (readBytes == -1)  
            err_exit("read socket error");  
        else if (readBytes != lenHost)  
        {  
            cerr << "server connect closed... \nexiting..." << endl;  
            break;  
        }  

        //将数据部分打印输出
        cout<<"msgType:"<<ntohl(buf.msgType)<<endl;
        cout << "returned from server: "<<endl
             <<text<<endl;
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

        memset(&buf, 0, sizeof(buf));
        memset(&oltIndex, 0, oltSize);
        memset(text, 0, 1024);
    }

    close(socketId);
    return 0;
}
