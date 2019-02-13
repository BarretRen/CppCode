#include "common.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <string.h>
#include <signal.h>

struct student
{
    char name[32];
    int age;
};

mqd_t mqid;

void handleSignal(int sig)
{
    mq_attr attr;
    if (mq_getattr(mqid, &attr) == -1)
        ERR_EXIT("mq_getattr failed");

    //读取消息队列中消息
    student rcvstu;
    unsigned prio;
    if(mq_receive(mqid, (char*)&rcvstu, attr.mq_msgsize, &prio) == -1)
        ERR_EXIT("mq_receive failed");

    printf("[mq_receive:%d] name:%s, age:%d, prio:%d\r\n", __LINE__, rcvstu.name, rcvstu.age, prio);

}

int main()
{
    mqid = mq_open("/abc", O_CREAT | O_RDWR, 0666, NULL);
    /** mqid = mq_open("/abc", O_RDWR, 0666, NULL); */
    if (mqid == (mqd_t)-1)
        ERR_EXIT("mq_open failed");
    

    signal(SIGUSR1, handleSignal);
    //注册消息通知
    sigevent evt;
    evt.sigev_notify = SIGEV_SIGNAL;
    evt.sigev_signo = SIGUSR1;
    mq_notify(mqid, &evt);//使用信号接收新消息通知
    
    //发送消息到消息队列
    student stu = {"barret", 29};
    if(mq_send(mqid, (const char*)&stu, sizeof(stu),  1) == -1)
        ERR_EXIT("mq_send failed");

    while(1)
    {
        pause();
    }

    mq_close(mqid); //关闭队列
    mq_unlink("/abc");//删除消息队列
    return 0;
}
