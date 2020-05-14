/*
����ֵfuture�Ķ�����;
*/
#include <future>
#include <iostream>
#include <thread>

int find_the_answer(int a, int b)
{
    return a + b;
}

void calculate_sum(int a, int b, std::promise<int> p)
{
    int sum = a + b;
    p.set_value(sum);//���ó�ŵֵ��֪ͨfuture
}

int main()
{
    //��;1���������̵߳ķ���ֵ
    // ���� async() �� future���첽����
    std::future<int> the_answer = std::async(find_the_answer, 1, 2);
    std::cout << "The async answer is " << the_answer.get() << std::endl;//����ֵͨ��future get()�������

    //��;2��ͨ��packaged_task�������񣬻�ȡ����ֵ
    //2.1���뺯�����ڵ���taskʱ�������
    std::packaged_task<int(int, int)> task1(find_the_answer); //���뺯����ģ����ָ������ֵ���������������
    std::future<int> f1 = task1.get_future();  // ��ȡ future
    task1(2, 3);//ֱ������task��ͬʱ�����ڲ�������Ҫ����
    std::cout << "The task1 answer is " << f1.get() << std::endl;//��ӡ����ֵ
    //2.2 ʹ��std::thread��ʼ��ʱΪtask�������
    std::packaged_task<int(int, int)> task2(find_the_answer); //���뺯����ģ����ָ������ֵ���������������
    std::future<int> f2 = task2.get_future();
    std::thread task2_th(std::move(task2), 3, 4);//�������
    task2_th.join();
    std::cout << "The task1 answer is " << f2.get() << std::endl;
    //2.3 ʹ��std::bind��װ�������������
    std::packaged_task<int()> task3(std::bind(find_the_answer, 4, 5));//ģ����ֻ��Ҫָ������ֵ����
    std::future<int> f3 = task3.get_future();
    task3();//ֱ������task��������Ҫ���ݲ���
    std::cout << "The task1 answer is " << f3.get() << std::endl;

    //��;3��ʹ��std::promise��future��Ϊ�̼߳��ź�
    std::promise<int> sum_promise;
    std::future<int> promise_future = sum_promise.get_future();
    std::thread promise_th(calculate_sum, 6, 7, std::move(sum_promise));//�����̣߳����뺯����������promise����
    promise_th.join();
    // // future::get() ���ȴ�ֱ���� future ӵ�кϷ������ȡ����, ������ get() ǰ���� wait()
    std::cout << "The promise_th answer is " << promise_future.get() << std::endl;
    
    return 0;
}