#include <linux/types.h>

#define SYS_SENDTO_ADDR (0xffffffffb50e3e20ULL)
#define SYS_RECVFROM_ADDR (0xffffffffb50e4070ULL)

int (*recvfrom)(int fd, void __user *ubuf, size_t size, unsigned int flags,
		   struct sockaddr __user *addr, int __user *addr_len) = SYS_RECVFROM_ADDR;

int (*sendto)(int fd, void __user *buff, size_t len, unsigned int flags,
		 struct sockaddr __user *addr,  int addr_len) = SYS_SENDTO_ADDR;