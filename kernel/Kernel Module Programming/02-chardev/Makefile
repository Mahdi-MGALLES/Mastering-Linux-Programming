obj-m = lkm_example.o
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod lkm_example.ko
  # Display the kernel log
	dmesg
