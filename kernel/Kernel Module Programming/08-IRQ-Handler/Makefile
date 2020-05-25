obj-m += keyboard_interrupt.o
 
KDIR = /lib/modules/$(shell uname -r)/build
 
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
load_mod:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod keyboard_interrupt.ko
  # Display the kernel log
	dmesg
mod_info:
	sudo modinfo keyboard_interrupt.ko
rm_mod:
	sudo rmmod keyboard_interrupt.ko
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
