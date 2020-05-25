obj-m += mutex.o
 
KDIR = /lib/modules/$(shell uname -r)/build
 
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
load_mod:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod mutex.ko
  # Display the kernel log
	dmesg
mod_info:
	sudo modinfo mutex.ko
rm_mod:
	sudo rmmod mutex.ko
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
