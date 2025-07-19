các file dành cho thiết bị là device file trong /dev

# Cấp phát device number
device number = major number + minor number
dùng để phân biệt thiết bị này với các thiết bị trên cùng hệ thống
tạo character device file
```
crw-rw----   1 root   disk     10, 234 Jul 19 07:06 btrfs-control
drwxr-xr-x   2 root   root        3620 Jul 19 07:06 char/
crw--w----   1 root   tty       5,   1 Jul 19 07:06 console
```
số bên trái gọi là major(10) number số bên phải là minor(234) number

### Cấp phát device number
cần thư viện  `#include <linux/fs.h>`
### class
bất cứ device nào cũng được nhóm vào class
các thiết bị thường nằm trong class nào đó `/sys/class/
Thêm 1 character device vào hệ thống thì phải khai báo file này nằm trong class nào
có thể tự tạo ra class