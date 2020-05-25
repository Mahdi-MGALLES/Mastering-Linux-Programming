obj-m = wait.o
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
load_mod:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod wait.ko
  # Display the kernel log
	dmesg
	sudo chmod 777 /dev/mychar0
mod_info:
	sudo modinfo wait.ko
rm_mod:
	sudo rmmod wait.ko
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
