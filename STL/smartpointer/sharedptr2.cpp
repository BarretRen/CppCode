//共享智能指针，自定自定义删除器的示例
#include <string>
#include <fstream>
#include <memory>
#include <cstdio>

class FileDeleter
{
private:
    std::string filename;

public:
    FileDeleter(const std::string &fn) : filename(fn) {}
    void operator()(std::ofstream *fp)
    {
        fp->close();                   //关闭文件
        std::remove(filename.c_str()); //删除文件
    }
};

int main()
{
    //创建临时文件，并指定删除器
    std::shared_ptr<std::ofstream> fp(new std::ofstream("tmpfile.txt"), FileDeleter("tmpfile.txt"));
    //...
}