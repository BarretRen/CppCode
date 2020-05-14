/*
ʹ��std::condition_variable���������� std::mutex ���ʹ�� ���Դٽ��̼߳�ͬ��
*/
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;//����������������ͬ��
std::string data;
bool ready = false;
bool processed = false;

void worker_thread()
{
    // �ȴ�ֱ�� main() ��������
    std::unique_lock<std::mutex> lk(m);
    //�����������ü�ض���͵ȴ�����������Ϊready��Ϊtrue�������������߳�һֱ�ȴ�
    cv.wait(lk, [] {return ready; });

    // �ȴ�������ռ������
    std::cout << "Worker thread is processing data\n";
    data += " after processing";

    // �������ݻ� main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";

    // ֪ͨǰ����ֶ��������Ա���ȴ��̲߳ű����Ѿ�����
    lk.unlock();
    cv.notify_one();//֪ͨһ���ȴ����̣߳�����ֻ�����߳�
}

int main11()
{
    std::thread worker(worker_thread);

    data = "Example data";
    // �������ݵ� worker �߳�
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();//ready�Ѿ����úã�֪ͨ���߳�

    // �Ⱥ� worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [] {return processed; });//���߳����������������ȵ����߳̽�processed��Ϊtrue
    }
    std::cout << "Back in main(), data = " << data << '\n';

    worker.join();
    return 0;
}