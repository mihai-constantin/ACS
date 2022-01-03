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


//this will declare buf[] and buf_len
#include "large_file.h"


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
	char *tmp;
	int ret;
	char *test_work_dir;
	char fpath[256];

	tmp = malloc(buf_len + 1000);
	FAIL_IF(!tmp, "malloc failed\n");

	install_hooks("so_stdio.dll", hooks, 1);

	if (argc == 2)
		test_work_dir = argv[1];
	else
		test_work_dir = "_test";

	sprintf(fpath, "%s/large_file", test_work_dir);

	ret = create_file_with_contents(fpath, buf, buf_len);
	FAIL_IF(ret != 0, "Couldn't create file: %s\n", fpath);


	/* --- BEGIN TEST --- */
	f = so_fopen(fpath, "a");
	FAIL_IF(!f, "Couldn't open file: %s\n", fpath);

	target_handle = so_fileno(f);

	num_WriteFile = 0;

	ret = so_fwrite(&buf[2000], 1, 1000, f);
	FAIL_IF(ret != 1000, "Incorrect return value for so_fread: got %d, expected %d\n", ret, 1000);
	FAIL_IF(num_WriteFile != 0, "Incorrect number of write syscalls: got %d, expected %d\n", num_WriteFile, 0);

	ret = so_fclose(f);
	FAIL_IF(ret != 0, "Incorrect return value for so_fclose: got %d, expected %d\n", ret, 0);

	FAIL_IF(num_WriteFile != 1, "Incorrect number of write syscalls: got %d, expected %d\n", num_WriteFile, 1);

	memcpy(tmp, buf, buf_len);
	memcpy(&tmp[buf_len], &buf[2000], 1000);

	FAIL_IF(!compare_file(fpath, (unsigned char *)tmp, buf_len + 1000), "Incorrect data in file\n");

	free(tmp);

	return 0;
}
