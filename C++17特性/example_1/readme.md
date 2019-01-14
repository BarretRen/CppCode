*****解释:**

在编写 C++ 时，也应该尽可能的避免使用诸如 void* 之类的程序风格。在不得不使用C时，应该注意使用extern "C" 这种特性，将 C 语言的代码与 C++ 代码进行分离编译，再统一链接的做法.

例子中使用clang 编译c代码，再使用clang++编译c++代码并链接c代码：

```shell
clang -c foo.c
clang++ example_1.cpp foo.o -std=c++17 -o example_1
```
