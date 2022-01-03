#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "so_stdio.h"
#include "test_util.h"

#include "hooks.h"

int num_sys_write;
int target_fd;

ssize_t hook_write(int fd, void *buf, size_t len);

struct func_hook hooks[] = {
	[0] = { .name = "write", .addr = (unsigned long)hook_write, .orig_addr = 0 },
};


char buf[] = "Hello, World!\n";
int buf_len = sizeof(buf) - 1;


ssize_t hook_write(int fd, void *buf, size_t len)
{
	ssize_t (*orig_write)(int, void *, size_t);

	orig_write = (ssize_t (*)(int, void *, size_t))hooks[0].orig_addr;

	if (fd == target_fd)
		num_sys_write++;

	return orig_write(fd, buf, len);
}


int main(int argc, char *argv[])
{
	SO_FILE *f;
	int c;
	int ret;
	char *test_work_dir;
	char fpath[256];

	install_hooks("libso_stdio.so", hooks, 1);

	if (argc == 2)
		test_work_dir = argv[1];
	else
		test_work_dir = "_test";

	sprintf(fpath, "%s/small_file", test_work_dir);


	/* --- BEGIN TEST --- */
	f = so_fopen(fpath, "w");
	FAIL_IF(!f, "Couldn't open file: %s\n", fpath);

	target_fd = so_fileno(f);

	num_sys_write = 0;

	// write 1 character
	c = so_fputc((int)buf[0], f);
	FAIL_IF((char)c != buf[0], "Incorrect character: got %x, expected %x\n", (unsigned char)c, buf[0]);

	// fputc should write to the buffer (shouldn't trigger any write syscall)
	FAIL_IF(num_sys_write != 0, "Incorrect number of write syscalls: got %d, expected %d\n", num_sys_write, 0);

	// write next character
	c = so_fputc((int)buf[1], f);
	FAIL_IF((char)c != buf[1], "Incorrect character: got %x, expected %x\n", (unsigned char)c, buf[1]);

	// fputc should write to the buffer (shouldn't trigger any write syscall)
	FAIL_IF(num_sys_write != 0, "Incorrect number of write syscalls: got %d, expected %d\n", num_sys_write, 0);

	ret = so_fclose(f);
	FAIL_IF(ret != 0, "Incorrect return value for so_fclose: got %d, expected %d\n", ret, 0);

	// fclose should flush the file and call the write syscall
	FAIL_IF(num_sys_write != 1, "Incorrect number of write syscalls: got %d, expected %d\n", num_sys_write, 1);

	FAIL_IF(!compare_file(fpath, (unsigned char *)buf, 2), "Incorrect data in file\n");

	return 0;
}
