/*
使用std::lock避免死锁
*/
#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <string>

struct Employee {
    Employee(std::string id) : id(id) {}
    std::string id;
    std::vector<std::string> lunch_partners;//午餐伙伴，互斥的
    std::mutex m;//互斥锁
    std::string output() const
    {
        std::string ret = "Employee " + id + " has lunch partners: ";
        for (const auto& partner : lunch_partners)
            ret += partner + " ";
        return ret;
    }
};

void send_mail(Employee&, Employee&)
{
    // 模拟耗时的发信操作
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
//分配伙伴
void assign_lunch_partner(Employee& e1, Employee& e2)
{
    static std::mutex io_mutex;
    {
        std::lock_guard<std::mutex> lk(io_mutex);//用于读输入参数内容的互斥锁，读完立刻释放
        std::cout << e1.id << " and " << e2.id << " are waiting for locks" << std::endl;
    }

    {
        // 用 std::lock获得二个employee的锁，而不担心对 assign_lunch_partner 的其他调用会死锁我们
        /*std::lock(e1.m, e2.m);
        std::lock_guard<std::mutex> lk1(e1.m, std::adopt_lock);
        std::lock_guard<std::mutex> lk2(e2.m, std::adopt_lock);*/
        // C++17 中可用的较优解法
        std::scoped_lock lk(e1.m, e2.m);
        {
            std::lock_guard<std::mutex> lk(io_mutex);//用于读输入参数内容的互斥锁，读完立刻释放
            std::cout << e1.id << " and " << e2.id << " got locks" << std::endl;
        }
        e1.lunch_partners.push_back(e2.id);//在lock的保护之下，可以放心的插入数据
        e2.lunch_partners.push_back(e1.id);
    }
    send_mail(e1, e2);
    send_mail(e2, e1);
}

int main7()
{
    //定义四个员工
    Employee alice("alice"), bob("bob"), christina("christina"), dave("dave");

    // 创建四个线程指派伙伴，因为发邮件给用户告知午餐指派，会消耗长时间
    std::vector<std::thread> threads;
    threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(alice));
    threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));
    //每个线程调用join
    for (auto& thread : threads) thread.join();
    //打印输出
    std::cout << alice.output() << '\n' << bob.output() << '\n'
        << christina.output() << '\n' << dave.output() << '\n';

    return 0;
}