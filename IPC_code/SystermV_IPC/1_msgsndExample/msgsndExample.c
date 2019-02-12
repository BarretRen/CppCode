#include "common.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("usage: %s <bytes> <type>\r\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int len = atoi(argv[1]);
    int type = atoi(argv[2]);
    int msgid = msgget(1234, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        msgid = msgget(1234, 0);
        if (msgid == -1)
            ERR_EXIT("msgget failed");
    }

    msgbuf* ptr = (msgbuf*)malloc(sizeof(long) + len);
    ptr->mtype = type;
    if (msgsnd(msgid, ptr, len, 0) < 0)
        ERR_EXIT("msgsnd failed");

    return 0;
}
