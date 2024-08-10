#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/ioctl.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include "lakeplacid.h"

#define FIRST_MINOR 0
#define MINOR_CNT 1

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Katherine Mohr");
MODULE_DESCRIPTION("rot13 echo server");

extern int handle_request(void);

static DECLARE_WAIT_QUEUE_HEAD(wq);
static struct task_struct *elite_thread;
static int data_ready = 0;

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;

void* __user_function_table[1024];
void* __kernel_function_table[1024];
void* __globals_table[1024];

extern void init_kernel_function_table(void);

ring_buffer* rb;
void* stack_space;

stack fast_stack = {0};

unsigned long long get_page_offset(void) {
    return PAGE_OFFSET;
}

static int driver_open(struct inode *device_file, struct file *instance) {
	printk("rot13 - open was called!\n");
	return 0;
}

static int driver_close(struct inode *device_file, struct file *instance) {
	printk("rot13 - close was called!\n");
	return 0;
}

static int set_params(lp_params *params) {
    if (copy_from_user(__globals_table, params->globals_table_addr, sizeof(__globals_table))) {
        return EFAULT;
    }

    if (copy_from_user(__user_function_table, params->user_function_table_addr, sizeof(__user_function_table))) {
        return EFAULT;
    }

    if (copy_from_user(rb, params->rb_addr, sizeof(rb))) {
        return EFAULT;
    }

    if (copy_from_user(stack_space, params->stack_space, sizeof(stack_space))) {
        return EFAULT;
    }

    // Set up the kernel table too
    init_kernel_function_table();

    return 0;
}

static ssize_t driver_read(struct file *file, char __user *buf, size_t count, loff_t *ppos) {
    wait_event_interruptible(wq, data_ready == 1);
    data_ready = 0;
    return 0;
}


static int do_work(void* data) {
    while (1) {
        switch_and_dispatch(handle_request);
    }
    return 0;
}

static long int example_ioctl(struct file *file, unsigned cmd, unsigned long arg){
    switch (cmd) {
        case LP_IOCTL_SET_PARAMS:
            return set_params((lp_params *)arg);
        case LP_IOCTL_INIT:
            if (elite_thread) {
                printk("Thread starting\n");
                wake_up_process(elite_thread);
                return 0;
            } else {
                printk("Thread creation failed\n");
                return -1;
            }
        default:
            return -EINVAL;
    }
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
  .read = driver_read,
	.unlocked_ioctl = example_ioctl
};

static int __init install_driver(void) {
  printk("Installing driver\n");
  
	int ret;
	struct device * dev_ret;

	if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "rot13_driver")) < 0) {
		return ret;
	}

	cdev_init(&c_dev, &fops);

	if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0) {
		return ret;
	}
	
	if (IS_ERR(cl = class_create(THIS_MODULE, "char"))) {
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(cl);
	}

	if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "rot13_driver"))) {
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(dev_ret);
	}

  elite_thread = kthread_create(do_work, NULL, "elite_thread");
  get_task_struct(elite_thread);

  printk("Driver installed\n");

  printk("PAGE_OFFSET: %lx\n", PAGE_OFFSET);
	
	return 0;
}

static void __exit uninstall_driver(void) {
  printk("Uninstalling driver\n");
  kthread_stop(elite_thread);
  put_task_struct(elite_thread);
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);	
}


module_init(install_driver);
module_exit(uninstall_driver);
