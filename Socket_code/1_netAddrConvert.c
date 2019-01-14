#include <stdio.h>
#include <arpa/inet.h>

int main(int, char**) {
	unsigned int a=0x12345678;
	unsigned char* p=(unsigned char*)&a;
	printf("%0x,%0x,%0x,%0x\r\n", p[0],p[1],p[2],p[3]);//打印本机字节序

	unsigned int b = htonl(a); //转换为网络字节序
	p=(unsigned char*)&b;
	printf("%0x,%0x,%0x,%0x\r\n", p[0],p[1],p[2],p[3]);

	unsigned long addr = inet_addr("192.168.0.100");
	printf("addr=%0x\r\n", ntohl(addr));

	struct in_addr ipaddr;
	ipaddr.s_addr = addr;
	printf("%s\r\n", inet_ntoa(ipaddr));
	return 0;
}
