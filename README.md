Part 1: Simple Kernel Module
Description

This part involves creating a simple kernel module that prints a message when it is loaded (initialized) and unloaded (exited) from the Linux kernel. The module will also demonstrate interaction with Netfilter hooks.
Files

    simple_module.c: The kernel module source code.
    Makefile: A Makefile to build the kernel module.

Instructions

    Build the Module:
        Run make in the directory containing the Makefile to compile the module.

    bash

make

Load the Module:

    Insert the module into the kernel using insmod.

bash

sudo insmod simple_module.ko

    Check the system logs to see the initialization message.

bash

dmesg | tail -n 20

Unload the Module:

    Remove the module from the kernel using rmmod.

bash

sudo rmmod simple_module

    Check the system logs to see the exit message.

bash

    dmesg | tail -n 20

Expected Output

    On module load: You should see a message like Simple kernel module loaded. in the system logs.
    On module unload: You should see a message like Simple kernel module unloaded. in the system logs.

Part 2: Netfilter Hook Integration
Description

This part extends the simple kernel module by integrating it with the Netfilter framework. The module will register to all five main Netfilter hooks and print a message every 10 seconds indicating in which hook the module is active.
Files

    netfilter_module.c: The kernel module source code that interacts with Netfilter hooks.
    Makefile: A Makefile to build the kernel module.

Instructions

    Build the Module:
        Run make in the directory containing the Makefile to compile the module.

    bash

make

Load the Module:

    Insert the module into the kernel using insmod.

bash

sudo insmod netfilter_module.ko

    The module will start printing messages to the system logs every 10 seconds.

Monitor the Output:

    Use dmesg to monitor the system logs and see the periodic messages indicating the active Netfilter hook.

bash

dmesg | tail -f

Unload the Module:

    Remove the module from the kernel using rmmod.

bash

    sudo rmmod netfilter_module

Expected Output

    Every 10 seconds, you should see a message like kernel module in X hook. in the system logs, where X is one of the Netfilter hooks.

Part 3: Security Feature Implementation
Description

This part involves creating a Netfilter-based kernel module that implements a security policy. The module blocks traffic from a specific IP address using Netfilter hooks.
Files

    firewall_module.c: The kernel module source code implementing the security feature.
    Makefile: A Makefile to build the kernel module.

Instructions

    Build the Module:
        Run make in the directory containing the Makefile to compile the module.

    bash

make

Load the Module:

    Insert the module into the kernel using insmod.

bash

sudo insmod firewall_module.ko

    The module will start blocking traffic from the specified IP address.

Test the Security Feature:

    Attempt to communicate with the blocked IP address and verify that the traffic is blocked.
    Use ping or another network utility to send traffic to the blocked IP address.

Unload the Module:

    Remove the module from the kernel using rmmod.

bash

    sudo rmmod firewall_module

Expected Output

    The system should block any traffic from or to the specified IP address. System logs will indicate when packets are dropped.

Resources Used

    Linux Kernel Module Programming Guide: https://tldp.org/LDP/lkmpg/2.6/html/index.html
    Netfilter Documentation: https://netfilter.org/documentation/index.html
    The Linux Kernel Module Programming Guide by Peter Jay Salzman, Michael Burian, Ori Pomerantz

These resources were used to understand kernel module development, Netfilter hooks, and implementing basic firewall functionality in the kernel.
How to Run

    Ensure you have a Linux development environment with kernel headers installed.
    Follow the build and load/unload instructions in each section to test the modules.
    Monitor system logs using dmesg to observe the output and verify that the modules are functioning as expected.


