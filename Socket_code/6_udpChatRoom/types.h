#ifndef _TYPES_H_
#define _TYPES_H_
#include <list>
#include <algorithm>

#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

#define MSG_LEN 512
enum chatTypes
{
    //client to server
    C2S_LOGIN = 0,
    C2S_LOGOUT,
    C2S_ONLINE_USER,
    //server to client
    S2C_LOGIN_OK,
    S2C_ALREADY_LOGINED,
    S2C_SOMEONE_LOGIN,
    S2C_SOMEONE_LOGOUT,
    S2C_ONLINE_USER,
    //client to client
    C2C_CHAT
};

struct message
{
    int msgType;
    char msgBody[MSG_LEN];
};

struct user_info
{
    char username[16];
    unsigned int ip;
    unsigned short port;
};

struct chat_msg
{
    char username[16];
    char msg[100];
};

typedef std::list<user_info> User_List;
#endif
