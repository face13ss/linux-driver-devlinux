EXTRA_CFLAGS = -Wall
obj-m = exam.o

# obj-m = exam.o => exam.ko // Nếu build ra file exam.ko thì được coi là build module
# Có thể dùng lệnh insmod or rmmod để tháo or bor module khỏi kernel tại runtime

# obj-y = exam.o => exam.o // Nếu build ra file exa,.o thì được gọi là built-in
# Module exam được tích hợp sẵn vào kernel image tại build time

KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd` modules
clean:
	make -C $(KDIR) M=`pwd` clean