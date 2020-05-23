/*
期望值future的多种用途
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
    p.set_value(sum);//设置承诺值，通知future
}

int main()
{
    //用途1，返回子线程的返回值
    // 来自 async() 的 future，异步任务
    std::future<int> the_answer = std::async(find_the_answer, 1, 2);
    std::cout << "The async answer is " << the_answer.get() << std::endl;//返回值通过future get()方法获得

    //用途2，通过packaged_task运行任务，获取返回值
    //2.1传入函数，在调用task时传入参数
    std::packaged_task<int(int, int)> task1(find_the_answer); //传入函数，模板中指定返回值和输入参数的类型
    std::future<int> f1 = task1.get_future();  // 获取 future
    task1(2, 3);//直接运行task，同时传入内部函数需要参数
    std::cout << "The task1 answer is " << f1.get() << std::endl;//打印返回值
    //2.2 使用std::thread初始化时为task输入参数
    std::packaged_task<int(int, int)> task2(find_the_answer); //传入函数，模板中指定返回值和输入参数的类型
    std::future<int> f2 = task2.get_future();
    std::thread task2_th(std::move(task2), 3, 4);//传入参数
    task2_th.join();
    std::cout << "The task1 answer is " << f2.get() << std::endl;
    //2.3 使用std::bind包装函数和输入参数
    std::packaged_task<int()> task3(std::bind(find_the_answer, 4, 5));//模板中只需要指定返回值类型
    std::future<int> f3 = task3.get_future();
    task3();//直接运行task，不再需要传递参数
    std::cout << "The task1 answer is " << f3.get() << std::endl;

    //用途3，使用std::promise和future作为线程间信号
    std::promise<int> sum_promise;
    std::future<int> promise_future = sum_promise.get_future();
    std::thread promise_th(calculate_sum, 6, 7, std::move(sum_promise));//构建线程，传入函数，参数和promise对象
    promise_th.join();
    // // future::get() 将等待直至该 future 拥有合法结果并取得它, 无需在 get() 前调用 wait()
    std::cout << "The promise_th answer is " << promise_future.get() << std::endl;
    
    return 0;
}