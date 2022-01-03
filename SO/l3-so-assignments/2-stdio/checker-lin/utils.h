/* SPDX-License-Identifier: GPL-2.0 */

/* CONSTANTIN MIHAI - 336CA */

#ifndef LIN_UTILS_H_
#define LIN_UTILS_H_	1

#include <stdio.h>
#include <stdlib.h>

/* useful macro for handling error codes */
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(EXIT_FAILURE);				\
		}							\
	} while (0)
#endif


ssize_t xread(int fd, void *buf, size_t count)
{
	size_t bytes_read = 0;
	ssize_t bytes_read_now;

	while(bytes_read < count) {

		bytes_read_now = read(fd, buf + bytes_read, count - bytes_read);

		printf("read: %ld\n", bytes_read_now);
		if (bytes_read_now == 0)
			break;

		if (bytes_read_now < 0)
			return -1;

		bytes_read += bytes_read_now;
	}

	return bytes_read;
}

ssize_t xwrite(int fd, void *buf, size_t count)
{
	size_t bytes_written = 0;
	ssize_t bytes_written_now;

	while (bytes_written < count) {
		bytes_written_now = write(fd, buf + bytes_written,
			count - bytes_written);

		if (bytes_written_now <= 0)
			return -1;

		bytes_written += bytes_written_now;
	}

	return bytes_written;
}











