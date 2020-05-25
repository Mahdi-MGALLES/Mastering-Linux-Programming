obj-m += mutex_char.o
 
KDIR = /lib/modules/$(shell uname -r)/build
 
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
load_mod:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod mutex_char.ko
  # Display the kernel log
	dmesg
	sudo chmod 777 /dev/mymutex0
mod_info:
	sudo modinfo mutex_char.ko
rm_mod:
	sudo rmmod mutex_char.ko
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
