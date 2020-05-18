/*
使用std::condition_variable条件变量与 std::mutex 组合使用 ，以促进线程间同步
*/
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;//定义条件变量用于同步
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    // 等待直至 main() 发送数据
    std::unique_lock<std::mutex> lk(m);
    //条件变量设置监控对象和等待条件，条件为ready变为true，否则阻塞本线程一直等待
    cv.wait(lk, [] {return ready; });

    // 等待后，我们占有锁。
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // 发送数据回 main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞
    lk.unlock();
    cv.notify_one();//通知一个等待的线程，这里只有主线程
}

int main11()
{
    std::thread worker(worker_thread);

    data = "Example data";
    // 发送数据到 worker 线程
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();//ready已经设置好，通知子线程

    // 等候 worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] {return processed; });//主线程设置条件变量，等到子线程将processed改为true
    }
    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
    return 0;
}