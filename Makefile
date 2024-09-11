# Makefile for building the our_kernel module

# Name of the module (without .c)
obj-m += our_kernel.o

# Default rule to build the module
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Rule to clean up the build artifacts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
