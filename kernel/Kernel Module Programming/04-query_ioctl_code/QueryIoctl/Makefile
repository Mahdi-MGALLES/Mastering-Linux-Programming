# If called directly from the command line, invoke the kernel build system.
ifeq ($(KERNELRELEASE),)

	KERNEL_SOURCE := /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)

default: module query_app

module:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) modules

test:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod query_ioctl.ko
  # Display the kernel log
	dmesg
	
info:
	modinfo query_ioctl.ko
	 
remove:
  # remove the kernel driver
	sudo rmmod query_ioctl.ko  
	
clean:
	$(MAKE) -C $(KERNEL_SOURCE) SUBDIRS=$(PWD) clean
	${RM} query_app

# Otherwise KERNELRELEASE is defined; we've been invoked from the
# kernel build system and can use its language.
else

	obj-m := query_ioctl.o

endif
