#include <linux/workqueue.h>
#include "kn_common.h"

MODULE_LICENSE("Dual BSD/GPL");

static void my_work_func(struct work_struct *);
static void my_custom_workqueue_func(struct work_struct *);

/* 静态创建一个工作，使用系统默认的工作者线程，即 events/n */
DECLARE_WORK(mywork, my_work_func);

static int testworkqueue_init(void)
{
    /*自定义的workqueue */
    struct workqueue_struct *myworkqueue = create_workqueue("myworkqueue");

    /* 动态创建一个工作 */
    struct work_struct *mywork2;
    mywork2 = kmalloc(sizeof(struct work_struct), GFP_KERNEL);
    INIT_WORK(mywork2, my_custom_workqueue_func);

    printk(KERN_ALERT "interrupt's top half! n");

    /* 刷新系统默认的队列 */
    flush_scheduled_work();
    /* 调度工作 */
    schedule_work(&mywork);

    /* 刷新自定义的工作队列 */
    flush_workqueue(myworkqueue);
    /* 调度自定义工作队列上的工作 */
    queue_work(myworkqueue, mywork2);

    return 0;
}

static void testworkqueue_exit(void)
{
    printk(KERN_ALERT "************************* n");
    print_current_time(0);
    printk(KERN_ALERT "my workqueue test is exited! n");
    printk(KERN_ALERT "************************* n");

}

static void my_work_func(struct work_struct *work)
{
    printk(KERN_ALERT "========================= n");
    print_current_time(0);
    printk(KERN_ALERT "my workqueue function is been called!.... n");
    printk(KERN_ALERT "========================= n");
}

static void my_custom_workqueue_func(struct work_struct *work)
{
    printk(KERN_ALERT "========================= n");
    print_current_time(0);
    printk(KERN_ALERT "my cutomize workqueue function is been called!.... n");
    printk(KERN_ALERT "========================= n");
    kfree(work);
}

module_init(testworkqueue_init);
module_exit(testworkqueue_exit);