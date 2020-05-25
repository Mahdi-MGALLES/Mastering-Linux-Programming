obj-m += rdwr_sem.o
 
KDIR = /lib/modules/$(shell uname -r)/build
 
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
load_mod:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod rdwr_sem.ko
  # Display the kernel log
	dmesg
	sudo chmod 777 /dev/mychar0
mod_info:
	sudo modinfo rdwr_sem.ko
rm_mod:
	sudo rmmod rdwr_sem.ko
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
