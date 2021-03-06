#include <sys/stat.h>
#include <errno.h>
#include "syscall.h"

void __procfdname(char *, unsigned);

int fchmod(int fd, mode_t mode)
{
	int ret = __syscall(SYS_fchmod, fd, mode);
	if (ret != -EBADF || fd < 0) return __syscall_ret(ret);

	char buf[15+3*sizeof(int)];
	__procfdname(buf, fd);
	return syscall(SYS_chmod, buf, mode);
}
