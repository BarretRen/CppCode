#include "common.h"
void handle_subprocess(int conn)
{
    char buf[1024];
    int ret;
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        ret = read(conn, buf, sizeof(buf));
        if (ret == -1)
        {
            if (ret == EINTR)
                continue;
            ERR_EXIT("read failed");
        }
        if (ret == 0)
        {
            printf("client closed\r\n");
            break;
        }
        printf("%s\r\n", buf);
        write(conn, buf, strlen(buf));
    }
    close(conn);
}

int main()
{
    int sock;
    //仍然使用socket函数创建socket，协议族指定为PF_UNIX
    if ((sock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
        ERR_EXIT("create unix socket failed");
    
    unlink("test socket");//先删除之前留下的socket文件
    sockaddr_un servaddr;
    servaddr.sun_family = AF_UNIX; //这里指定unix域协议
    strcpy(servaddr.sun_path, "test socket"); //指定socket文件，会再目录下生成该名称的文件

    //bind
    if (bind(sock, (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        ERR_EXIT("bind failed");

    //listen
    if (listen(sock, SOMAXCONN) < 0)
        ERR_EXIT("listen failed");

    int conn;
    pid_t pid;
    while(1)
    {
        conn = accept(sock, NULL, NULL);
        if (conn == -1)
        {
            if (conn == EINTR)
                continue;
            ERR_EXIT("accept failed");
        } 
        pid = fork();
        if (pid == -1)
            ERR_EXIT("fork failed");
        if (pid == 0)//子进程
        {
            close(sock);
            handle_subprocess(conn);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(conn);
        }
    }
    close(sock);
    return 0;
}
