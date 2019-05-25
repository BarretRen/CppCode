#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/delay.h>
#include "kn_common.h"

MODULE_LICENSE("Dual BSD/GPL");

static void test_short_delay(void);
static void test_delay(void);
static void test_schedule_timeout(void);
static void my_delay_function(unsigned long);

static int testdelay_init(void)
{
    printk(KERN_ALERT "HZ in current system: %dHz\n", HZ);

    /* test short delay */
    test_short_delay();

    /* test delay */
    test_delay();

    /* test schedule timeout */
    test_schedule_timeout();

    return 0;
}

static void testdelay_exit(void)
{
    printk(KERN_ALERT "*************************\n");
    print_current_time(0);
    printk(KERN_ALERT "testdelay is exited!\n");
    printk(KERN_ALERT "*************************\n");
}

static void test_short_delay()
{
    printk(KERN_ALERT "jiffies [b e f o r e] short delay: %lu", jiffies);
    ndelay(5);
    printk(KERN_ALERT "jiffies [a f t e r] short delay: %lu", jiffies);
}

static void test_delay()
{
    /* 初始化定时器 */
    struct timer_list my_timer;
    init_timer(&my_timer);

    /* 填充定时器 */
    my_timer.expires = jiffies + 1*HZ; /* 2秒后超时函数执行 */
    my_timer.data = jiffies;
    my_timer.function = my_delay_function;

    /* 激活定时器 */
    add_timer(&my_timer);
}

static void my_delay_function(unsigned long data)
{
    printk(KERN_ALERT "This is my delay function start......\n");
    printk(KERN_ALERT "The jiffies when init timer: %lu\n", data);
    printk(KERN_ALERT "The jiffies when timer is running: %lu\n", jiffies);
    printk(KERN_ALERT "This is my delay function end........\n");
}

static void test_schedule_timeout()
{
    printk(KERN_ALERT "This sample start at : %lu", jiffies);

    /* 睡眠2秒 */
    set_current_state(TASK_INTERRUPTIBLE);
    printk(KERN_ALERT "sleep 2s ....\n");
    schedule_timeout(2*HZ);

    printk(KERN_ALERT "This sample end at : %lu", jiffies);
}

module_init(testdelay_init);
module_exit(testdelay_exit);
