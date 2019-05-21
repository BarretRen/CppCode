#include <linux/interrupt.h>
#include "kn_common.h"

MODULE_LICENSE("Dual BSD/GPL");

static void my_softirq_func(struct softirq_action*);

static int testsoftirq_init(void)
{
    // 注册softirq，这里注册的是定时器的下半部
    open_softirq(TIMER_SOFTIRQ, my_softirq_func);

    // 触发softirq
    raise_softirq(TIMER_SOFTIRQ);

    return 0;

}

static void testsoftirq_exit(void)
{
    printk(KERN_ALERT "************************* n");
    print_current_time(0);
    printk(KERN_ALERT "testrbtree is exited! n");
    printk(KERN_ALERT "************************* n");

}

static void my_softirq_func(struct softirq_action* act)
{
    printk(KERN_ALERT "========================= n");
    print_current_time(0);
    printk(KERN_ALERT "my softirq function is been called!.... n");
    printk(KERN_ALERT "========================= n");
}

module_init(testsoftirq_init);
module_exit(testsoftirq_exit);