#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#include <linux/semaphore.h>

static struct semaphore my_sem;
static int counter = 0;
static struct task_struct *thread_st;

// Function executed by kernel thread



static int thread_fn(void *unused)
{
    while (!kthread_should_stop())
    {
        if (down_interruptible(&my_sem))
            break;
        counter++;
        printk(KERN_INFO "Job %d started\n", counter);
        //get_random_bytes(&i, sizeof(i));
        ssleep(3);
        printk(KERN_INFO "Job %d finished\n", counter);
        up(&my_sem);
    }
    printk(KERN_INFO "Thread Stopping\n");
    do_exit(0);
}
// Module Initialization
static int __init init_thread(void)
{
	printk(KERN_INFO "Creating Thread\n");
    //Create the kernel thread with name 'mythread'
    thread_st = kthread_run(thread_fn, NULL, "mythread");
    if (thread_st)
        printk(KERN_INFO "Thread Created successfully\n");
    else
        printk(KERN_ERR "Thread creation failed\n");
    sema_init(&my_sem, 1);
    return 0;
}
// Module Exit
static void __exit cleanup_thread(void)
{
	printk(KERN_INFO "Cleaning Up\n");
	if (thread_st)
	{
		kthread_stop(thread_st);
		printk(KERN_INFO "Thread stopped");
	}
}
MODULE_LICENSE("GPL");
module_init(init_thread);
module_exit(cleanup_thread);
