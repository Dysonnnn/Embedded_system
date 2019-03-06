ifneq ($(KERNELRELEASE),)
	obj-m := hello.o
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
#	KERNELDIR ?= /usr/src/linux-source-4.15.0
#	KERNELDIR ?= /usr/src/linux-2.6.10
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm *.o *.ko
endif


