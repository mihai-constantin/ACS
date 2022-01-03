/**
  * SO, 2017
  * Lab #3
  *
  * Task #4, lin
  *
  * FIFO server
  */
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "utils.h"
#include "common.h"	/* PIPE_NAME, BUFSIZE */

#include "xfile.h"

int main(void)
{
	int fd, bytesRead, rc;
	char buff[BUFSIZE];

	/* TODO - create named pipe */
	rc = mkfifo(PIPE_NAME, 0644);
	DIE(rc < 0, "create named pipe failed!");

	/* TODO - open named pipe */
	fd = open(PIPE_NAME, O_RDONLY);
	DIE(fd < 0, "open named pipe failed!");

	/* TODO - read in buff from pipe while not EOF */
	memset(buff, 0, sizeof(buff));

	while(1) {

		bytesRead = xread(fd, buff, BUFSIZE);
		DIE(bytesRead < 0, "bytesRead failed!");	

		if(bytesRead == 0) {
			break;
		}
	}
	
	printf("Message received:%s\n", buff);

	/* Close and delete pipe */
	rc = close(fd);
	DIE(rc < 0, "close");

	rc = unlink(PIPE_NAME);
	DIE(rc < 0, "unlink");

	return 0;
}
