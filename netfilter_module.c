#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

static struct nf_hook_ops nfho_pre, nfho_in, nfho_forward, nfho_out, nfho_post;
static struct timer_list my_timer;

// Netfilter hook function
static unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    printk(KERN_INFO "Kernel module in %s hook.\n", 
           state->hook == NF_INET_PRE_ROUTING ? "NF_INET_PRE_ROUTING" :
           state->hook == NF_INET_LOCAL_IN ? "NF_INET_LOCAL_IN" :
           state->hook == NF_INET_FORWARD ? "NF_INET_FORWARD" :
           state->hook == NF_INET_LOCAL_OUT ? "NF_INET_LOCAL_OUT" :
           "NF_INET_POST_ROUTING");
    return NF_ACCEPT;
}

// Timer callback function
void my_timer_callback(struct timer_list *timer) {
    printk(KERN_INFO "Timer: 10 seconds have passed.\n");

    // Re-arm the timer for another 10 seconds
    mod_timer(timer, jiffies + msecs_to_jiffies(10000));
}

// Setup and start the timer
static void setup_timer(void) {
    timer_setup(&my_timer, my_timer_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(10000));
}

// Module initialization function
static int __init my_module_init(void) {
    // Pre-routing hook
    nfho_pre.hook = hook_func;
    nfho_pre.hooknum = NF_INET_PRE_ROUTING;
    nfho_pre.pf = PF_INET;
    nfho_pre.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_pre);

    // Local-in hook
    nfho_in.hook = hook_func;
    nfho_in.hooknum = NF_INET_LOCAL_IN;
    nfho_in.pf = PF_INET;
    nfho_in.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_in);

    // Forward hook
    nfho_forward.hook = hook_func;
    nfho_forward.hooknum = NF_INET_FORWARD;
    nfho_forward.pf = PF_INET;
    nfho_forward.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_forward);

    // Local-out hook
    nfho_out.hook = hook_func;
    nfho_out.hooknum = NF_INET_LOCAL_OUT;
    nfho_out.pf = PF_INET;
    nfho_out.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_out);

    // Post-routing hook
    nfho_post.hook = hook_func;
    nfho_post.hooknum = NF_INET_POST_ROUTING;
    nfho_post.pf = PF_INET;
    nfho_post.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_post);

    // Set up the timer
    setup_timer();

    printk(KERN_INFO "Kernel module loaded.\n");
    return 0;
}

// Module exit function
static void __exit my_module_exit(void) {
    // Unregister the hooks
    nf_unregister_net_hook(&init_net, &nfho_pre);
    nf_unregister_net_hook(&init_net, &nfho_in);
    nf_unregister_net_hook(&init_net, &nfho_forward);
    nf_unregister_net_hook(&init_net, &nfho_out);
    nf_unregister_net_hook(&init_net, &nfho_post);

    // Remove the timer
    del_timer(&my_timer);

    printk(KERN_INFO "Kernel module exiting.\n");
}

// Register module initialization and exit functions
module_init(my_module_init);
module_exit(my_module_exit);

// Module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Team2");
MODULE_DESCRIPTION("Kernel Module with Netfilter Hooks and Timer");
