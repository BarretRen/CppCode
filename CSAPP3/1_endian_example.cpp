//一个检查大小端的示例
#include <iostream>
typedef unsigned char *pointer;

//该函数用于打印输入数值的内存地址和对应的值
//由此可以看出是什么字节序
void show_bytes(pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++)
        printf("%p\t 0x%.2x\n", start + i, start[i]);
    printf("\n");
}

int main()
{
    int a = 15213; //16进制位0x3b6d
    show_bytes((pointer)&a, sizeof(int));
    return 0;
}