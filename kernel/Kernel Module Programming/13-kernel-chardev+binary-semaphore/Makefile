obj-m += sem_char.o
 
KDIR = /lib/modules/$(shell uname -r)/build
 
 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
load_mod:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod sem_char.ko
  # Display the kernel log
	dmesg
	sudo chmod 777 /dev/mysem0
mod_info:
	sudo modinfo sem_char.ko
rm_mod:
	sudo rmmod sem_char.ko
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
