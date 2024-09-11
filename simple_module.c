#include <linux/module.h>  // Needed for all kernel modules
#include <linux/kernel.h>  // Needed for KERN_INFO
#include <linux/init.h>    // Needed for the macros

// Module initialization function
static int __init simple_init(void)
{
    printk(KERN_INFO "Simple Module: Initialization\n");
    return 0;  // Return 0 indicates successful loading
}

// Module exit function
static void __exit simple_exit(void)
{
    printk(KERN_INFO "Simple Module: Exiting\n");
}

// Register the initialization and exit functions
module_init(simple_init);
module_exit(simple_exit);

// Module Information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matan");
MODULE_DESCRIPTION("A Simple Linux Kernel Module");
