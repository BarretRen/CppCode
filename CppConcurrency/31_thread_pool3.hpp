//线程池，在30线程池中为每个线程建立独立的任务队列
#ifndef THREAD_POOL3
#define THREAD_POOL3
#include <future>
#include <atomic>
#include <vector>
#include <queue>
#include "21_threadsafe_queue2.hpp"
#include "29_thread_pool.hpp"

/*std::packaged_task<>实例是不可拷贝的，仅是可移动的，所以不能再使用std::function<>来实现任务队列
因为std::function<>需要存储可复制构造的函数对象。
这里包装一个自定义函数，用来处理只可移动的类型，就是一个带有函数操作符的类型擦除类
*/
class function_wrapper
{
private:
    struct impl_base
    {
        virtual void call() = 0;
        virtual ~impl_base() {}
    };

    std::unique_ptr<impl_base> impl;

    template <typename F>
    struct impl_type : impl_base
    {
        F f;
        impl_type(F &&f_) : f(std::move(f_)) {}
        void call() { f(); }
    };

public:
    template <typename F>
    function_wrapper(F &&f) : impl(new impl_type<F>(std::move(f)))
    {
    }

    function_wrapper() = default;

    function_wrapper(function_wrapper &&other) : impl(std::move(other.impl))
    {
    }

    function_wrapper &operator=(function_wrapper &&other)
    {
        impl = std::move(other.impl);
        return *this;
    }

    void operator()() { impl->call(); }

    function_wrapper(const function_wrapper &) = delete;
    function_wrapper(function_wrapper &) = delete;
    function_wrapper &operator=(const function_wrapper &) = delete;
};

class thread_pool3
{
private:
    std::atomic_bool done;
    threadsafe_queue<function_wrapper> work_queue; // 使用function_wrapper，而非使用std::function
    typedef std::queue<function_wrapper> local_queue_type;
    static thread_local std::unique_ptr<local_queue_type> local_work_queue; // unique_ptr指向每个线程本地（thread_local)的工作队列
    std::vector<std::thread> threads;                                       // 保存pool里的工作线程
    join_threads joiner;                                                    // join_threads使用RAII方式，保证pool销毁前所有线程能执行结束

    void worker_thread()
    {
        local_work_queue.reset(new local_queue_type); // 3
        while (!done)
        {
            run_pending_task();
        }
    }

public:
    thread_pool3() : done(false), joiner(threads)
    {
        // pool中线程个数使用硬件支持的最大个数
        unsigned const thread_count = std::thread::hardware_concurrency();

        try
        {
            for (unsigned i = 0; i < thread_count; ++i)
            {
                // 创建工作线程，每个线程都执行worker_thread函数，在此函数中获取任务处理
                threads.push_back(std::thread(&thread_pool3::worker_thread, this));
            }
        }
        catch (...)
        {
            done = true; // 有异常时，设置done为true
            throw;
        }
    }

    ~thread_pool3()
    {
        done = true;
    }
    // submit返回一个保存任务返回值的future，使用result_of获取函数functionType的返回类型
    template <typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type>
    submit(FunctionType f)
    {
        // 设置函数functionType的返回类型的别名为result_type
        typedef typename std::result_of<FunctionType()>::type result_type;

        std::packaged_task<result_type()> task(std::move(f)); // 封装一个异步任务，任务执行函数f
        std::future<result_type> res(task.get_future());      // 获取异步任务的future
        if (local_work_queue)                                 // 检查当前线程是否具有一个工作队列，如果有则将任务放入本地队列
        {
            local_work_queue->push(std::move(task));
        }
        else
        {
            work_queue.push(std::move(task)); // 将任务添加到全局任务队列中
        }

        return res; // 返回future给submit函数的调用者
    }
    /*
    run_pending_task()的实现去掉了在worker_thread()函数的主循环。
    函数任务队列中有任务的时候执行任务，要是没有的话就会让操作系统对线程进行重新分配。
    */
    void run_pending_task()
    {
        function_wrapper task;
        if (local_work_queue && !(local_work_queue->empty())) // 如果本地队列有任务，则优先处理本地队列的任务
        {
            task = std::move(local_work_queue->front());
            local_work_queue->pop();
            task();
        }
        else if (work_queue.try_pop(task)) //否则，在全局队列获取任务
        {
            task();
        }
        else
        {
            std::this_thread::yield();
        }
    }
};
#endif