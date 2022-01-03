// SPDX-License-Identifier: GPL-2.0

/* CONSTANTIN MIHAI - 336CA */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include "exec_parser.h"
#include "utils.h"

static so_exec_t *exec;

static int pageSize;
static struct sigaction old_action;

static int fd;

static void segv_handler(int signum, siginfo_t *info, void *context)
{
	char *addr, *p;
	int i;
	int page_found;
	int pages_no;
	int pageIdx;
	uintptr_t u_addr;
	uintptr_t page_addr;

	/* segment properties */
	uintptr_t vaddr;
	unsigned int file_size;
	unsigned int mem_size;
	unsigned int offset;
	unsigned int perm;
	int *data;

	pageSize = getpagesize();

	if (signum != SIGSEGV) {
		/* run default handler */
		old_action.sa_sigaction(signum, info, context);
		return;
	}

	/* page fault address */
	addr = (char *)info->si_addr;

	page_found = 0;

	/* iterate through segments */
	for (i = 0; i < exec->segments_no; i++) {
		so_seg_t segment = exec->segments[i];

		/* get segment properties */
		vaddr = segment.vaddr;
		file_size = segment.file_size;
		mem_size = segment.mem_size;
		offset = segment.offset;
		perm = segment.perm;
		data = (int *)segment.data;

		pages_no = mem_size / pageSize;
		if (mem_size % pageSize)
			++pages_no;

		/* verify if segment contains addr */
		u_addr = (uintptr_t)addr;
		if (u_addr >= vaddr && u_addr < vaddr + mem_size) {

			page_found = 1;

			/* get page's index */
			pageIdx = (int)(u_addr - vaddr) / pageSize;

			/* page already mapped -> run default handler */
			if (data[pageIdx]) {
				old_action.sa_sigaction(signum, info, context);
				return;
			}

			/* get starting page address */
			page_addr = vaddr + pageSize * pageIdx;

			p = mmap((void *)page_addr, pageSize, perm, 
				MAP_FIXED | MAP_PRIVATE, fd, offset + pages_no * pageSize);

			DIE(p == MAP_FAILED, "mmap");

			// /* memset */
			// if (mem_size > pages_no * pageSize &&
			// 	mem_size <= (pages_no + 1) * pageSize) {
			// 	memset(p, 0, (size_t)(mem_size - pages_no * pageSize));
			// }
			// else
			// if (file_size < (pages_no + 1) * pageSize &&
			// 	file_size >= pages_no * pageSize &&
			// 	mem_size > (pages_no + 1) * pageSize) {
			// 	memset((void *)(vaddr + file_size), 0,
			// 		(size_t)((pages_no + 1) * pageSize - file_size));
			// }

			/* set pageIdx */
			data[pageIdx] = 1;

			return;
		}
	}

	if (!page_found) {
		/* run default handler */
		old_action.sa_sigaction(signum, info, context);
		return;
	}
}

int so_init_loader(void)
{
	/* routine for SIGSEGV */
	struct sigaction sa;
	int rc;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = segv_handler;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGSEGV);

	sa.sa_flags = SA_SIGINFO;

	rc = sigaction(SIGSEGV, &sa, &old_action);

	if (rc == -1)
		return -1;

	return 0;
}

int so_execute(char *path, char *argv[])
{
	int i, pages_no, pageSize;
	unsigned int mem_size;

	pageSize = getpagesize();

	fd = open(path, O_RDONLY);
	DIE(fd < 0, "open");

	exec = so_parse_exec(path);
	if (!exec)
		return -1;

	for (i = 0; i < exec->segments_no; i++) {
		so_seg_t *segment = &(exec->segments[i]);

		mem_size = segment->mem_size;
		pages_no = mem_size / pageSize;
		if (mem_size % pageSize)
			++pages_no;

		/* initially, every data is set to 0 for every page */
		segment->data = calloc(pages_no, sizeof(int));
	}

	so_start_exec(exec, argv);

	return -1;
}


