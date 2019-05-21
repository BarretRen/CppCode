#include "kn_common.h"

MODULE_LICENSE("Dual BSD/GPL");
struct student
{
    int id;
    char* name;
};

static void print_student(struct student*);

static int testkfifo_init(void)
{
    struct kfifo *fifo;
    struct student *stu1, *stu2, *stu3, *stu4;
    struct student *stu_tmp;
    char* c_tmp;
    int i;
    // !!importent  init a unlocked lock
    static DEFINE_SPINLOCK(sl);

    // init kfifo
    kfifo_alloc(fifo, 4*sizeof(struct student), GFP_KERNEL);

    stu1 = kmalloc(sizeof(struct student), GFP_KERNEL);
    stu1->id = 1;
    stu1->name = "wyb1";
    kfifo_put(fifo, stu1);

    stu2 = kmalloc(sizeof(struct student), GFP_KERNEL);
    stu2->id = 1;
    stu2->name = "wyb2";
    kfifo_put(fifo, stu2);

    stu3 = kmalloc(sizeof(struct student), GFP_KERNEL);
    stu3->id = 1;
    stu3->name = "wyb3";
    kfifo_put(fifo, stu3);

    stu4 = kmalloc(sizeof(struct student), GFP_KERNEL);
    stu4->id = 1;
    stu4->name = "wyb4";
    kfifo_put(fifo, stu4);

    c_tmp = kmalloc(sizeof(struct student), GFP_KERNEL);
    printk(KERN_ALERT "current fifo length is : %d\n", kfifo_len(fifo));
    for (i=0; i < 4; i++) {

        kfifo_get(fifo, c_tmp, sizeof(struct student));
        stu_tmp = (struct student *)c_tmp;
        print_student(stu_tmp);
        printk(KERN_ALERT "current fifo length is : %d\n", kfifo_len(fifo));
    }

    printk(KERN_ALERT "current fifo length is : %d\n", kfifo_len(fifo));
    kfifo_free(fifo);
    kfree(c_tmp);
    return 0;
}

static void print_student(struct student *stu)
{
    printk(KERN_ALERT "=========================\n");
    print_current_time(1);
    printk(KERN_ALERT "id = %d\n", stu->id);
    printk(KERN_ALERT "name = %s\n", stu->name);
    printk(KERN_ALERT "=========================\n");
}

static void testkfifo_exit(void)
{
    printk(KERN_ALERT "*************************\n");
    printk(KERN_ALERT "testkfifo is exited!\n");
    printk(KERN_ALERT "*************************\n");
}

module_init(testkfifo_init);
module_exit(testkfifo_exit);
