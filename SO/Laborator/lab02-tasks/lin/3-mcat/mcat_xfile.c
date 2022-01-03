/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #3, Linux
 *
 * cat/cp applications
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"
#include "xfile.h"

#define BUFSIZE		32

int main(int argc, char **argv)
{
	int fd_src, fd_dst, rc, bytesRead, bytesWritten;
	char buffer[BUFSIZE];

	if (argc < 2 || argc > 3) {
		printf("Usage:\n\t%s source_file [destination_file]\n",
			argv[0]);
		return 0;
	}

	/* TODO 1 - open source file for reading */
	fd_src = open(argv[1], O_RDONLY);
	DIE(fd_src < 0, "open source file failed!");

	if (argc == 3) {
		/* TODO 2 - redirect stdout to destination file */
		fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		DIE(fd_dst < 0, "open destination file failed!");
		close(STDOUT_FILENO);
		dup(fd_dst);

	}

    /* TODO 3 - Change the I/O strategy and implement xread/xwrite. These
     * functions attempt to read _exactly_ the size provided as parameter.
     */

	while(1) {

	 	bytesRead = xread(fd_src, buffer, BUFSIZE);
	 	DIE(bytesRead < 0, "xread failed!");
		
		if(bytesRead == 0) {
        	break;
        }

	 	bytesWritten = xwrite(STDOUT_FILENO, buffer, bytesRead);
	 	DIE(bytesWritten <= 0, "xread failed!");
	 }

	/* TODO 1 - close file */
	rc = close(fd_src);
	DIE(rc < 0, "close fd_src");

	if(argc == 3) {
		rc = close(fd_dst);
		DIE(rc < 0, "close fd_dst");
	}


	return 0;
}

