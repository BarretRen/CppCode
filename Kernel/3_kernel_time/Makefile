obj-m := mydelay.o
mydelay-objs := testdelay.o kn_common.o

#generate the path
CURRENT_PATH:=$(shell pwd)
#the absolute path
LINUX_KERNEL_PATH:=/usr/src/linux-source-4.15.0  #直接用发行版中的linux源码，不用再下载linux内核源码。注意，每个linux发行版的目录不一定一样
#complie object
all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
