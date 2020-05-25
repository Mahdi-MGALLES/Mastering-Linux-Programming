obj-m += driver.o
 
KDIR = /lib/modules/$(shell uname -r)/build
 
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
load_mod:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod driver.ko
  # Display the kernel log
	dmesg
mod_info:
	sudo modinfo driver.ko
rm_mod:
	sudo rmmod driver.ko
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
