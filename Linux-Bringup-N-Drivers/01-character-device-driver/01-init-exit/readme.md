# Cách build linux module cơ bản

linux source code trong trang bootlin
# Tải header để build
sudo apt install linux-headers-`uname -r`
# kiểm tra dung lượng
du -hs <dir>

# Đọc thông tin ở kernel
dmesg -w
# insert module
sudo insmod exam.ko
# remove module
sudo rmmod exam.ko
# module information
$ modinfo exam.ko
filename:       /home/dungla/Documents/devlinux2/Linux-Bringup-N-Drivers/01-character-device-driver/01-init-exit/exam.ko
version:        1.0
description:    Hello world kernel module
author:         dungla anhdungxd21@mail.com
license:        GPL
srcversion:     D8BC01A4E4F95BD5A48A599
depends:        
retpoline:      Y
name:           exam
vermagic:       6.11.0-26-generic SMP preempt mod_unload modversions 