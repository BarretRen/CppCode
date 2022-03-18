typedef signed long ssize_t;
typedef unsigned long size_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

struct T_LogicalIndex
{
    uint16_t ifType;
    uint16_t logical;
    uint16_t slot;
    uint16_t powerLevel;
    uint16_t temperature;
    uint16_t voltage;
    uint16_t biasCurrent;
};

enum TelemetryMsgType
{
    PON_OLT_OPTICS_INFO=0,
    TELEMETRY_UNKNOWN
};

struct Packet
{
    unsigned int  msgLen;     //数据部分的长度(注：这是网络字节序)    
    unsigned int  msgType;
};

#define err_exit(m) \
    do { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

ssize_t	 readn(int, char *, size_t);
ssize_t	 writen(int, const char *, size_t);

