typedef signed long ssize_t;
typedef unsigned long size_t;

struct Packet    
{    
    unsigned int      msgLen;     //数据部分的长度(注：这是网络字节序)    
    char            text[1024]; //报文的数据部分    
};

#define err_exit(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

ssize_t	 readn(int, void *, size_t);
ssize_t	 writen(int, const void *, size_t);

