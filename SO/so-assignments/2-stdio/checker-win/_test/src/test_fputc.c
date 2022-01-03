#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

#include "so_stdio.h"
#include "test_util.h"

#include "hooks.h"

int num_WriteFile;
HANDLE target_handle;

BOOL WINAPI hook_WriteFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

struct func_hook hooks[] = {
	{ "kernel32.dll", "WriteFile", (unsigned long)hook_WriteFile, 0 },
};


char buf[] = "Hello, World!\n";
int buf_len = sizeof(buf) - 1;


BOOL WINAPI hook_WriteFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
	BOOL (WINAPI *orig_WriteFile)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED) =
		(BOOL (WINAPI *)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED))hooks[0].orig_addr;

	if (hFile == target_handle)
		num_WriteFile++;

	return orig_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}


int main(int argc, char *argv[])
{
	SO_FILE *f;
	int c;
	int ret;
	char *test_work_dir;
	char fpath[256];

	install_hooks("so_stdio.dll", hooks, 1);

	if (argc == 2)
		test_work_dir = argv[1];
	else
		test_work_dir = "_test";

	sprintf(fpath, "%s/small_file", test_work_dir);


	/* --- BEGIN TEST --- */
	f = so_fopen(fpath, "w");
	FAIL_IF(!f, "Couldn't open file: %s\n", fpath);

	target_handle = so_fileno(f);

	num_WriteFile = 0;

	// write 1 character
	c = so_fputc((int)buf[0], f);
	FAIL_IF((char)c != buf[0], "Incorrect character: got %x, expected %x\n", (unsigned char)c, buf[0]);

	// fputc should write to the buffer (shouldn't trigger any write syscall)
	FAIL_IF(num_WriteFile != 0, "Incorrect number of write syscalls: got %d, expected %d\n", num_WriteFile, 0);

	// write next character
	c = so_fputc((int)buf[1], f);
	FAIL_IF((char)c != buf[1], "Incorrect character: got %x, expected %x\n", (unsigned char)c, buf[1]);

	// fputc should write to the buffer (shouldn't trigger any write syscall)
	FAIL_IF(num_WriteFile != 0, "Incorrect number of write syscalls: got %d, expected %d\n", num_WriteFile, 0);

	ret = so_fclose(f);
	FAIL_IF(ret != 0, "Incorrect return value for so_fclose: got %d, expected %d\n", ret, 0);

	// fclose should flush the file and call the write syscall
	FAIL_IF(num_WriteFile != 1, "Incorrect number of write syscalls: got %d, expected %d\n", num_WriteFile, 1);

	FAIL_IF(!compare_file(fpath, (unsigned char *)buf, 2), "Incorrect data in file\n");

	return 0;
}
