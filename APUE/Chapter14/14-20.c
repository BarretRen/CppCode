//ROT-13翻译算法
#include "../include/apue.h"
#include <ctype.h>
#include <fcntl.h>

#define BSZ 4096

unsigned char buf[BSZ];

unsigned char
translate(unsigned char c)
{
    //算法主体
	if (isalpha(c)) {
		if (c >= 'n')
			c -= 13;
		else if (c >= 'a')
			c += 13;
		else if (c >= 'N')
			c -= 13;
		else
			c += 13;
	}
	return(c);
}

int
main(int argc, char* argv[])
{
	int	ifd, ofd, i, n, nw;

	if (argc != 3)
		err_quit("usage: rot13 infile outfile");
	if ((ifd = open(argv[1], O_RDONLY)) < 0)  //打开输入文件
		err_sys("can't open %s", argv[1]);
	if ((ofd = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0) //打开输出文件
		err_sys("can't create %s", argv[2]);

	while ((n = read(ifd, buf, BSZ)) > 0) {
		for (i = 0; i < n; i++)
			buf[i] = translate(buf[i]);   //对每个字符进行翻译
		if ((nw = write(ofd, buf, n)) != n) { //写入文件
			if (nw < 0)
				err_sys("write failed");
			else
				err_quit("short write (%d/%d)", nw, n);
		}
	}

	fsync(ofd); //缓冲区写入内存
	exit(0);
}
