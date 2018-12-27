#include "common.h"
#define MSGMAX 8192

int main(int argc, char* argv[])
{
    int flag = 0;
    int type =0;
    int opt;
    while(1)
    {
        opt = getopt(argc, argv, "nt:"); //通过getopt获取输入选项-n，-t
        if (opt == '?')
            exit(EXIT_FAILURE);
        if (opt == -1)
            break;

        switch (opt)
        {
            case 'n':
                flag |= IPC_NOWAIT;
                break;
            case 't':
                type = atoi(optarg);
                break;
        }
    }

    int msgid;
    int rcvsize = 0;
    msgid = msgget(1234, 0);
    if (msgid == -1)
        ERR_EXIT("msgget failed");

    msgbuf* ptr = (msgbuf*)malloc(sizeof(long) + MSGMAX);
    ptr->mtype = type;
    if ((rcvsize = msgrcv(msgid, ptr, MSGMAX, type, flag)) < 0)
        ERR_EXIT("msgrcv failed");

    printf("read %d bytes from msg queue\r\n", rcvsize);
    return 0;
}
