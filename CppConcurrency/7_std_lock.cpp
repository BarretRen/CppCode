/*
ʹ��std::lock��������
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
    std::vector<std::string> lunch_partners;//��ͻ�飬�����
    std::mutex m;//������
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
    // ģ���ʱ�ķ��Ų���
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
//������
void assign_lunch_partner(Employee& e1, Employee& e2)
{
    static std::mutex io_mutex;
    {
        std::lock_guard<std::mutex> lk(io_mutex);//���ڶ�����������ݵĻ����������������ͷ�
        std::cout << e1.id << " and " << e2.id << " are waiting for locks" << std::endl;
    }

    {
        // �� std::lock��ö���employee�������������Ķ� assign_lunch_partner ���������û���������
        /*std::lock(e1.m, e2.m);
        std::lock_guard<std::mutex> lk1(e1.m, std::adopt_lock);
        std::lock_guard<std::mutex> lk2(e2.m, std::adopt_lock);*/
        // C++17 �п��õĽ��Žⷨ
        std::scoped_lock lk(e1.m, e2.m);
        {
            std::lock_guard<std::mutex> lk(io_mutex);//���ڶ�����������ݵĻ����������������ͷ�
            std::cout << e1.id << " and " << e2.id << " got locks" << std::endl;
        }
        e1.lunch_partners.push_back(e2.id);//��lock�ı���֮�£����Է��ĵĲ�������
        e2.lunch_partners.push_back(e1.id);
    }
    send_mail(e1, e2);
    send_mail(e2, e1);
}

int main()
{
    //�����ĸ�Ա��
    Employee alice("alice"), bob("bob"), christina("christina"), dave("dave");

    // �����ĸ��߳�ָ�ɻ�飬��Ϊ���ʼ����û���֪���ָ�ɣ������ĳ�ʱ��
    std::vector<std::thread> threads;
    threads.emplace_back(assign_lunch_partner, std::ref(alice), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(bob));
    threads.emplace_back(assign_lunch_partner, std::ref(christina), std::ref(alice));
    threads.emplace_back(assign_lunch_partner, std::ref(dave), std::ref(bob));
    //ÿ���̵߳���join
    for (auto& thread : threads) thread.join();
    //��ӡ���
    std::cout << alice.output() << '\n' << bob.output() << '\n'
        << christina.output() << '\n' << dave.output() << '\n';
}