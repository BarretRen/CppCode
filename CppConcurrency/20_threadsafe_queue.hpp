/*
基于锁和条件变量的线程安全队列
*/
template <typename T>
class threadsafe_queue
{
private:
    //互斥量m用于保证线程安全，对每个成员函数进行加锁保护，保证在同一时间只有一个线程可以访问数据
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T>> data_queue; //使用std::shared_ptr实例，而不是直接使用数据的值
    std::condition_variable data_cond;         //条件变量

public:
    threadsafe_queue() {}

    void push(T new_value)
    {
        std::shared_ptr<T> data(std::make_shared<T>(std::move(new_value))); // 5
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one(); //通知一个等待条件变量的线程
    }

    void wait_and_pop(T &value)
    {
        std::unique_lock<std::mutex> lk(mut);
        //使用条件变量等待条件达成，比循环调用empty()要好很多
        data_cond.wait(lk, [this] { return !data_queue.empty(); });
        value = std::move(*data_queue.front()); // 1
        data_queue.pop();
    }

    bool try_pop(T &value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = std::move(*data_queue.front()); // 2
        data_queue.pop();
        return true;
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this] { return !data_queue.empty(); });
        std::shared_ptr<T> res = data_queue.front(); // 3
        data_queue.pop();
        return res;
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res = data_queue.front(); // 4
        data_queue.pop();
        return res;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
};