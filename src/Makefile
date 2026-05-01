obj-m += timer_driver.o
KDIR := ~/linux
CROSS := riscv64-linux-gnu-

all:
	make ARCH=riscv CROSS_COMPILE=$(CROSS) -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
