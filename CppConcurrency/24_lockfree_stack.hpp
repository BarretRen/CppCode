//无锁的线程安全栈
#include <atomic>
#include <memory>

template <typename T>
class lock_free_stack
{
private:
    struct node
    {
        std::shared_ptr<T> data; //使用共享指针保存数据
        node *next;

        node(const T &data) : data(std::make_shared(data)), next(nullptr) {}
    };

    std::atomic<node *> head; //原子操作类

public:
    /*
    push操作：
    1. 创建一个新的节点node
    2. 让node->next指向head->next
    3. head->next指向node
    */
    void push(T const &data)
    {
        node *const new_node = new node(data); // 1
        // 2 node->next先指向head，这里会有多线程等待，如果别的线程在操作head的话
        new_node->next = head.load(); //使用默认内存序
        /*
        3 使用“比较-交换”更新head：
        判断当前head是不是new_node->next(用来判断是否其他线程修改了head)：
            返回false，则当前head不是new_node->next，则更新new_node->next为新的head，然后继续循环直到返回true
            返回true，则表示没有其他线程修改head，则替换head和new_node位置（new_node变成head之后的第一个了），跳出循环
        */
        while (!head.compare_exchange_weak(new_node->next, new_node))
            ;
    }

    /*
    pop操作：
    1. 获取head。
    2. 读取head->next指向的结点node。
    3. 设置head->next指向node->next。
    4. 通过node返回携带的数据data。
    5. 删除node节点。
    */
    std::shared_ptr<T> pop()
    {
        node *old_head = head.load(); //先获得head，多线程等待，防止别的线程正在获取head
        /*
        使用“比较-交换”更新head：
        判断当前head是否等于old_head，即head有无发生变化
            返回false，即head发生变化，old_head更新为新的head，继续循环
            返回true，即head没有变化，则替换head和head->next的位置，跳出循环
        */
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next)) //old_head不能为空指针
            ;
        return old_head ? old_head->data : std::shared_ptr<T>();//返回数据或空指针
        //注意，old_head并没有从内存中删除，有内存泄漏
    }
};