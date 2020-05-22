//无锁的线程安全栈
#include <atomic>
#include <memory>

template <typename T>
class lock_free_stack
{
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
        ++threads_in_pop;             //新线程调用pop，增加计数1
        node *old_head = head.load(); //先获得head，多线程等待，防止别的线程正在获取head
        /*
        使用“比较-交换”更新head：
        判断当前head是否等于old_head，即head有无发生变化
            返回false，即head发生变化，old_head更新为新的head，继续循环
            返回true，即head没有变化，则替换head和head->next的位置，跳出循环
        */
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next)) //old_head不能为空指针
            ;
        //此时的old_head为第一个有数据的节点，真正的head是它的next
        std::shared_ptr<T> retVal;
        if (old_head)
        {
            retVal.swap(old_head->data); //交换内容，将old_head的data传递给retVal
        }
        try_reclaim(old_head); //回收old_head节点，计数器减一
        return retVal;
    }

private:
    struct node
    {
        std::shared_ptr<T> data; //使用共享指针保存数据
        node *next;

        node(const T &data) : data(std::make_shared(data)), next(nullptr) {}
    };

    std::atomic<node *> head;             //原子操作类
    std::atomic<unsigned> threads_in_pop; //原子计数，记录当前多少个线程在调用pop
    std::atomic<node *> to_be_deleted;    //将要删除的节点列表，暂存，因为不能立刻删除，其他线程可能还在用

    //释放node
    static void delete_nodes(node *nodes)
    {
        while (nodes)
        {
            node *next = nodes->next;
            delete nodes;
            nodes = next;
        }
    }

    void chain_pending_nodes(node *nodes)
    {
        node *last = nodes;
        while (node *const next = last->next) // 9 让next指针指向链表的末尾
        {
            last = next;
        }
        chain_pending_nodes(nodes, last);
    }

    void chain_pending_nodes(node *first, node *last)
    {
        last->next = to_be_deleted;
        while (!to_be_deleted.compare_exchange_weak(last->next, first)) // 用循环来保证last->next的正确性
            ;
    }
    void chain_pending_node(node *n)
    {
        chain_pending_nodes(n, n);
    }

    void try_reclaim(node *old_head)
    {
        if (threads_in_pop == 1) // 当计数为1，表示只有当前线程正在调用pop函数，可以删除节点
        {
            // 返回to_be_deleted的第一个值值给左边，同时to_be_deleted赋值nullptr，因为to_be_deleted中可能有多个等待中的节点
            node *nodes_to_delete = to_be_deleted.exchange(nullptr);
            if (!--threads_in_pop) // 计数器减一，再次确认是否只有一个线程调用pop()
            {
                delete_nodes(nodes_to_delete); // 循环删除等待列表中的节点
            }
            else if (nodes_to_delete)
            {
                chain_pending_nodes(nodes_to_delete); // 6
            }
            delete old_head; // 删除新传入的节点
        }
        else
        {
            chain_pending_node(old_head); // 计数不是1，将节点添加到等待删除列表
            --threads_in_pop;             //计数减一
        }
    }
};