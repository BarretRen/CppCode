/*
基于锁的线程安全栈
*/
#ifndef THREAD_SAFE_TASK
#define THREAD_SAFE_TASK
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
//自定义异常
struct empty_stack : std::exception
{
    const char *what() const throw();
};

template <typename T>
class threadsafe_stack
{
private:
    std::stack<T> data; //封装的标准库stack
    //互斥量m用于保证线程安全，对每个成员函数进行加锁保护，保证在同一时间只有一个线程可以访问数据
    mutable std::mutex m; //mutable表示可变的，const的反义词

public:
    threadsafe_stack() {}
    //拷贝构造函数
    threadsafe_stack(const threadsafe_stack &other)
    {
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    }
    //不允许自动生成赋值构造函数，标记为delete
    threadsafe_stack &operator=(const threadsafe_stack &) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value)); // 1
    }
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack(); // 2
        std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top()))); // 3
        data.pop();                                      // 4
        return res;
    }
    void pop(T &value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        value = std::move(data.top()); // 5
        data.pop();                    // 6
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};
#endif