obj-m = wait.o
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
test:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod wait.ko
  # Display the kernel log
	dmesg
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
