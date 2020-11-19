//测试epoll函数的LT和ET模式
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <stdbool.h>
#include <libgen.h>

#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

//设置描述符为非阻塞模式
int setNonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}
//添加描述符到epoll事件表，可以指定LT or ET模式
void addfd(int epollfd, int fd, bool enableET)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN; //监听数据可读事件
    if (enableET)
        event.events |= EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setNonblocking(fd);
}
//LT模式下工作流程
void lt_flow(struct epoll_event *event, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; i++)
    {
        int sockfd = event[i].data.fd;
        if (sockfd == listenfd) //epoll返回的是监听中的socket，说明有新客户端连接
        {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            //接受客户端连接
            int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);
            addfd(epollfd, connfd, false); //LT模式，加入到epoll事件表
        }
        else if (event[i].events & EPOLLIN) //有数据可读
        {
            //因为是LT模式，socket缓存中有未读出的数据，就会触发EPOLLIN事件
            printf("event trigger once\n");
            memset(buf, 0, BUFFER_SIZE);
            int ret = recv(sockfd, buf, BUFFER_SIZE - 1, 0);
            if (ret <= 0)
            {
                close(sockfd); //出异常了，关闭socket
                continue;
            }
            printf("get %d bytes of connets: %s\n", ret, buf);
        }
        else
        {
            printf("something else happened\n");
        }
    }
}
//ET模式下工作流程
void et_flow(struct epoll_event *event, int number, int epollfd, int listenfd)
{
    char buf[BUFFER_SIZE];
    for (int i = 0; i < number; i++)
    {
        int sockfd = event[i].data.fd;
        if (sockfd == listenfd) //epoll返回的是监听中的socket，说明有新客户端连接
        {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            //接受客户端连接
            int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);
            addfd(epollfd, connfd, true); //ET模式，加入到epoll事件表
        }
        else if (event[i].events & EPOLLIN) //有数据可读
        {
            //因为是ET模式，只会触发一次EPOLLIN事件，所以需要在这里一次性读完数据
            printf("event trigger once\n");
            while (1)
            {
                memset(buf, 0, BUFFER_SIZE);
                int ret = recv(sockfd, buf, BUFFER_SIZE - 1, 0);
                if (ret < 0)
                {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                    { //判断用于非阻塞IO，表示数据全部读完，等待下一次数据可读，不关闭sockfd
                        printf("read later\n");
                        break;
                    }
                    close(sockfd); //出异常了，关闭socket
                    break;
                }
                else if (ret == 0)
                {
                    close(sockfd); //数据读完，关闭socket
                }
                else
                {
                    printf("get %d bytes of connets: %s\n", ret, buf);
                }
            }
        }
        else
        {
            printf("something else happened\n");
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("Usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    const int port = atoi(argv[2]);
    int ret = 0;

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET; //IPv4
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret >= 0);

    ret = listen(listenfd, 5); //最大连接数5
    assert(ret >= 0);

    //创建epoll并添加socket到事件表中
    struct epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    assert(epollfd >= 0);
    addfd(epollfd, listenfd, true);

    while(1)
    {
        //使用epoll等待事件触发，可能是新客户端连接，可能是数据可写
        ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if(ret < 0)
        {
            printf("epoll failed\n");
            break;
        }
        //选择LT或ET模式处理
        lt_flow(events, ret, epollfd, listenfd);
        // et_flow(events, ret, epollfd, listenfd);
    }
    close(listenfd);
    return 0;
}