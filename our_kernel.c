#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/inet.h>

// Define the IPv4 address to block (in string format)
#define BLOCKED_IPV4 "192.168.1.184"

// Netfilter hook option struct
static struct nf_hook_ops nfho_pre, nfho_local_in;

// Function to check if the IPv4 address matches the blocked address
static bool is_ipv4_blocked(__be32 ip)
{
    __be32 blocked_ip = in_aton(BLOCKED_IPV4);
    return ip == blocked_ip;
}

// Netfilter hook function
static unsigned int hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    struct iphdr *ip_header = (struct iphdr *)skb_network_header(skb);

    // Print the source IP address and the hook it was captured in
    printk(KERN_INFO "Packet received in hook %d from: %pI4\n", state->hook, &ip_header->saddr);

    // Check if the source IP is blocked
    if (is_ipv4_blocked(ip_header->saddr)) {
        printk(KERN_INFO "Dropping packet from blocked IPv4: %pI4\n", &ip_header->saddr);
        return NF_DROP;  // Drop the packet
    }

    return NF_ACCEPT;  // Accept the packet
}

// Module initialization function
static int __init my_module_init(void)
{
    // Register for the PRE_ROUTING hook
    nfho_pre.hook = hook_func;
    nfho_pre.hooknum = NF_INET_PRE_ROUTING;
    nfho_pre.pf = PF_INET;
    nfho_pre.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_pre);

    // Register for the LOCAL_IN hook
    nfho_local_in.hook = hook_func;
    nfho_local_in.hooknum = NF_INET_LOCAL_IN;
    nfho_local_in.pf = PF_INET;
    nfho_local_in.priority = NF_IP_PRI_FIRST;
    nf_register_net_hook(&init_net, &nfho_local_in);

    printk(KERN_INFO "IPv4 blocking module loaded.\n");
    return 0;
}

// Module cleanup function
static void __exit my_module_exit(void)
{
    nf_unregister_net_hook(&init_net, &nfho_pre);
    nf_unregister_net_hook(&init_net, &nfho_local_in);
    printk(KERN_INFO "IPv4 blocking module unloaded.\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matan");
MODULE_DESCRIPTION("Kernel module for blocking a specific IPv4 address");
