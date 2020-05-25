//最简单的线程池，仅用于示例
#ifndef THREAD_POOL
#define THREAD_POOL
#include <thread>
#include <atomic>
#include <vector>
#include <functional>
#include "21_threadsafe_queue2.hpp"

class join_threads
{
private:
    std::vector<std::thread> &threads;

public:
    explicit join_threads(std::vector<std::thread> &threads_) : threads(threads_)
    {
    }
    ~join_threads()
    {
        for (unsigned long i = 0; i < threads.size(); ++i)
        {
            // 析构函数中等待线程结束，RAII方式
            if (threads[i].joinable())
                threads[i].join();
        }
    }
};

class thread_pool
{
private:
    //注意这里声明的顺序，是为了保证析构时能以相反的顺序销毁（很重要）
    std::atomic_bool done;
    threadsafe_queue<std::function<void()>> work_queue; // 使用线程安全队列保存任务
    std::vector<std::thread> threads;                   // 保存pool里的工作线程
    join_threads joiner;                                // join_threads使用RAII方式，保证pool销毁前所有线程能执行结束

    void worker_thread()
    {
        while (!done) // 原子bool设置为true时，保证每个正在运行的线程停止
        {
            std::function<void()> task;
            if (work_queue.try_pop(task)) // 从任务队列获取到一个任务
            {
                task(); // 执行任务，函数指针
            }
            else
            {
                std::this_thread::yield(); // 没有任务，当前线程放弃执行，线程休息
            }
        }
    }

public:
    thread_pool() : done(false), joiner(threads)
    {
        // pool中线程个数使用硬件支持的最大个数
        unsigned const thread_count = std::thread::hardware_concurrency();

        try
        {
            for (unsigned i = 0; i < thread_count; ++i)
            {
                // 创建工作线程，每个线程都执行worker_thread函数，在此函数中获取任务处理
                threads.push_back(std::thread(&thread_pool::worker_thread, this));
            }
        }
        catch (...)
        {
            done = true; // 有异常时，设置done为true
            throw;
        }
    }

    ~thread_pool()
    {
        done = true; // 11
    }
    // submit将一个要执行的任务包装成std::function函数指针，加入任务队列
    template <typename FunctionType>
    void submit(FunctionType f)
    {
        work_queue.push(std::function<void()>(f)); // 12
    }
};
#endif