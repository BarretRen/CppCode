#include <linux/rbtree.h>
#include <linux/string.h>
#include "kn_common.h"

MODULE_LICENSE("Dual BSD/GPL");
struct student
{
    int id;
    char* name;
    struct rb_node node;
};

static int insert_student(struct student*, struct rb_root*);
static int remove_student(struct student*, struct rb_root*);
static int display_student(struct rb_root*, int);
static void display_student_from_small(struct rb_node*);
static void display_student_from_big(struct rb_node*);
static void print_student(struct student*);

static int testrbtree_init(void)
{
#define N 10
    struct rb_root root = RB_ROOT;
    struct student *stu[N];
    char tmp_name[5] = {'w', 'y', 'b', '0', '\0'};
    int i;

    // init N struct student
    for (i=0; i<N; i++)
    {
        stu[i] = kmalloc(sizeof(struct student), GFP_KERNEL);
        stu[i]->id = i;
        stu[i]->name = kmalloc(sizeof(char)*5, GFP_KERNEL);
        tmp_name[3] = (char)(i+48);
        strcpy(stu[i]->name, tmp_name);
        // stu_name[3] = (char)(i+48);
        stu[i]->node.rb_left = NULL;
        stu[i]->node.rb_right = NULL;
    }

    for (i=0; i < N; ++i)
    {
        printk(KERN_ALERT "id=%d   name=%s\n", stu[i]->id, stu[i]->name);
    }

    // add N student to rbtree
    print_current_time(0);
    for (i=0; i < N; i++)
        insert_student(stu[i], &root);

    // display all students
    printk(KERN_ALERT "print from small to big!\n");
    display_student(&root, -1);
    printk(KERN_ALERT "print from big to small!\n");
    display_student(&root, 1);

    // delete student 8
    remove_student(stu[7], &root);
    display_student(&root, -1);

    // free all student
    for (i=0; i<N; ++i)
    {
        kfree(stu[i]->name);
        kfree(stu[i]);
    }

    return 0;
}

static int insert_student(struct student* stu, struct rb_root* root)
{
    struct rb_node* parent;
    struct rb_node* tmp_rb;
    struct student* tmp_stu;

    /* first time to insert node */
    if (!root->rb_node) 
    {
        root->rb_node = &(stu->node);
        rb_set_parent(&(stu->node), NULL);
        rb_set_black(&(stu->node));
        return 0;
    }

    /* find where to insert node */
    tmp_rb = root->rb_node;
    while(tmp_rb)
    {
        parent = tmp_rb;
        tmp_stu = rb_entry(tmp_rb, struct student, node);

        if (tmp_stu->id > stu->id) 
            tmp_rb = parent->rb_left;
        else if (tmp_stu->id < stu->id)
            tmp_rb = parent->rb_right;
        else
            break;
    }

    /* the student's id  is already in the rbtree */
    if (tmp_rb)
    {
        printk(KERN_ALERT "this student has been inserted!\n");
        return 1;
    }

    if (tmp_stu->id > stu->id)
        parent->rb_left = &(stu->node);
    else
        parent->rb_right = &(stu->node);

    rb_set_parent(&(stu->node), parent);
    rb_insert_color(&(stu->node), root);

    return 0;
}

static int remove_student(struct student* stu, struct rb_root* root)
{
    rb_erase(&(stu->node), root);

    return 0;
}

static int display_student(struct rb_root *root, int order)
{
    if (!root->rb_node)
        return 1;
    if (order < 0)
        display_student_from_small(root->rb_node);
    else
        display_student_from_big(root->rb_node);

    return 0;
}

static void display_student_from_small(struct rb_node* node)
{
    struct student *tmp_stu;

    if (node)
    {
        display_student_from_small(node->rb_left);
        tmp_stu = rb_entry(node, struct student, node);
        print_student(tmp_stu);
        display_student_from_small(node->rb_right);
    }
}

static void display_student_from_big(struct rb_node* node)
{
    struct student *tmp_stu;

    if (node)
    {
        display_student_from_big(node->rb_right);
        tmp_stu = rb_entry(node, struct student, node);
        print_student(tmp_stu);
        display_student_from_big(node->rb_left);
    }
}

static void print_student(struct student* stu)
{
    printk(KERN_ALERT "=========================\n");
    print_current_time(0);
    printk(KERN_ALERT "id=%d\tname=%s\n", stu->id, stu->name);
    printk(KERN_ALERT "=========================\n");
}

static void testrbtree_exit(void)
{
    printk(KERN_ALERT "*************************\n");
    print_current_time(0);
    printk(KERN_ALERT "testrbtree is exited!\n");
    printk(KERN_ALERT "*************************\n");

}

module_init(testrbtree_init);
module_exit(testrbtree_exit);