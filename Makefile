# Makefile for building kernel modules

# Name of the modules (without .c)
obj-m += netfilter_module.o
obj-m += our_kernel.o
obj-m += simple_module.o

# Default rule to build the modules
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Rule to clean up the build artifacts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
