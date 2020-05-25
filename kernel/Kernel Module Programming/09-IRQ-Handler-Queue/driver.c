/*
*   irq_ex2.c: An interrupt handler example. This code binds itself to `IRQ` 1, which
*   is the IRQ of the keyboard controlled under Intel architectures. Then, when it
*   receives a keyboard interrupt, it reads the information about status led and keycode
*   into the work queue. Pressing:
*       ESC   ---> Caps Lock Led OFF
*       F1,F2 ---> Caps Lock ON
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mahdi MGALLES");

/*
*   Define const for LED on keyboard
*/
#define SCROLL_LED 1
#define NUM_LED 2
#define CAPS_LED 4
#define MY_WORK_QUEUE_NAME "WQ_schedule"

/* Prototype set led on keyboard */
void set_led(int, int, int);

/* Global variable */
unsigned char status_led =0;
static struct workqueue_struct *my_workqueue;
typedef struct {
  struct work_struct my_work;
  unsigned char keycode;        /* Save scancode for workqueue */
} my_work_t;

my_work_t *work;

/*
*  got_char: This function will get called by the kernel as soon as it's safe
*  to do everything normally allowed by Kernel modules
*/
static void got_char(struct work_struct *work)
{
    my_work_t *my_work = (my_work_t *)work;
    if(my_work->keycode == 0x01)
          printk(KERN_INFO "! You pressed ESC... \n");
    if(my_work->keycode == 0x3C)
          printk(KERN_INFO "! You pressed F2... \n");

    //printk(KERN_INFO "--> LED on Caps Lock: %s.\n",status_led & CAPS_LED ? "ON" :"OFF");
    kfree( (void *)work );
    return;
}
/*
*   Function: set_led: Set status LED on keyboard
*/
void set_led(int scroll_led, int num_led, int caps_led)
{

  /* Take argument to set status_led */
  status_led = (scroll_led) ? (status_led | SCROLL_LED):(status_led & SCROLL_LED);
  status_led = (num_led) ? (status_led | NUM_LED):(status_led & NUM_LED);
  status_led = (caps_led) ? (status_led | CAPS_LED):(status_led & CAPS_LED);

  /* Read keyboard status*/
   while((inb(0x64)&2)!=0){}
  /* Send command 0xED to port 0x60 to set LED*/
  outb(0xED,0x60);
  /* Read keyboard status again*/
  while((inb(0x64)&2)!=0){}
  /* Send value to LED on keyboard*/
  outb(status_led,0x60);
}

/*
*   This function service keyboard interrupts. It reads the relevant
*   information from the keyboard and then puts the information about
*   status led and keycode into the work queue. This will be run when
*   the kernel considers it safe.
*/
irqreturn_t irq_handler(int irq, void *dev_id)
{
  /*
* This variables are static because they need to be
* accessible (through pointers) to the bottom half routine.
*/
  static unsigned char scancode;
  unsigned char status;

/*
* Read keyboard status
*/
  status = inb(0x64);
  scancode = inb(0x60);

switch (scancode)
{
  case 0x01:  printk (KERN_INFO "! You pressed Esc ...+++\n");
              msecs_to_jiffies(500);
              //set_led(0,0,0);
              break;
  case 0x3B:  printk (KERN_INFO "! You pressed F1 ...+++\n");
              msecs_to_jiffies(500);
              //set_led(1,1,1);
              break;
  case 0x3C:  printk (KERN_INFO "! You pressed F2 ...+++\n");
              msecs_to_jiffies(500);
              //set_led(0,0,1);
              break;
  default:
              break;
}

  work = (my_work_t *) kmalloc(sizeof(my_work_t),GFP_KERNEL);
  work->keycode = scancode;
  INIT_WORK((struct work_struct *)work,got_char);
  queue_work(my_workqueue,(struct work_struct *) work);

  return IRQ_HANDLED;
}

static int __init irq_ex_init (void)
{
    printk(KERN_INFO "! Module is load ... \n");
    my_workqueue = create_workqueue(MY_WORK_QUEUE_NAME);
    /* Free interrupt keyboard */
    free_irq(1,NULL);

    return request_irq(1,(irq_handler_t) irq_handler, IRQF_SHARED,"test_keyboard_irq_handler",(void *)(irq_handler));
}

static void __exit irq_ex_exit (void)
{
    printk(KERN_INFO "! Module is unload ...\n");
    free_irq(1,(void *)(irq_handler));
}

module_init(irq_ex_init);
module_exit(irq_ex_exit);
