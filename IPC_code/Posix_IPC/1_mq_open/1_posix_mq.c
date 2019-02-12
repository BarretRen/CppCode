#include "common.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <string.h>

struct student
{
    char name[32];
    int age;
};

int main()
{
    mqd_t mqid;
    mqid = mq_open("/abc", O_CREAT | O_RDWR, 0666, NULL);
    /** mqid = mq_open("/abc", O_RDWR, 0666, NULL); */
    if (mqid == (mqd_t)-1)
        ERR_EXIT("mq_open failed");
    
    //获取消息队列参数
    mq_attr attr;
    if (mq_getattr(mqid, &attr) == -1)
        ERR_EXIT("mq_getattr failed");

    printf("[mq_getattr:%d]  mq_flags:%d, mq_maxmsg:%d, mq_msgsize:%d, mq_curmsgs:%d\r\n", __LINE__, attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    //发送消息到消息队列
    student stu = {"barret", 29};
    if(mq_send(mqid, (const char*)&stu, sizeof(stu),  1) == -1)
        ERR_EXIT("mq_send failed");

    if (mq_getattr(mqid, &attr) == -1)
        ERR_EXIT("mq_getattr failed");

    printf("[mq_getattr:%d]  mq_flags:%d, mq_maxmsg:%d, mq_msgsize:%d, mq_curmsgs:%d\r\n", __LINE__, attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    //读取消息队列中消息
    student rcvstu;
    unsigned prio;
    if(mq_receive(mqid, (char*)&rcvstu, attr.mq_msgsize, &prio) == -1)
        ERR_EXIT("mq_receive failed");

    printf("[mq_receive:%d] name:%s, age:%d, prio:%d\r\n", __LINE__, rcvstu.name, rcvstu.age, prio);

    if (mq_getattr(mqid, &attr) == -1)
        ERR_EXIT("mq_getattr failed");

    printf("[mq_getattr:%d]  mq_flags:%d, mq_maxmsg:%d, mq_msgsize:%d, mq_curmsgs:%d\r\n", __LINE__, attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    mq_close(mqid); //关闭队列
    mq_unlink("/abc");//删除消息队列
    return 0;
}
