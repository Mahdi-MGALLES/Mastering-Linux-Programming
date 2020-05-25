
obj-m	:= proc.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

all: default

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	$(CC) -o usertest usertest.c
	
test:
  # Clear the kernel log without echo
	sudo dmesg -C
  # Insert the module
	sudo insmod proc.ko
  # Display the kernel log
	dmesg
	
info:
	modinfo proc.ko
	 
remove:
  # remove the kernel driver
	sudo rmmod proc.ko                      
		
clean:
	rm -rf *.o usertest *~ core .depend .*.cmd *.mod *.ko *.md *.mod.c *.order *.symvers .tmp_versions

