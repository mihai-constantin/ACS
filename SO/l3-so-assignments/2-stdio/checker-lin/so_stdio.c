// SPDX-License-Identifier: GPL-2.0

/* CONSTANTIN MIHAI - 336CA */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/wait.h>
#include <sys/types.h>	/* open */
#include <sys/stat.h>	/* open */
#include <fcntl.h>		/* O_RDWR, O_CREAT, O_TRUNC, O_WRONLY */
#include <unistd.h>		/* lseek, close */

#include "utils.h"
#include "so_stdio.h"

#define READ_OP  0
#define WRITE_OP 1
#define FFLUSH_OP 2
#define FSEEK_OP 3

#define ERROR 12

#define BUFSIZE 4096

struct _so_file {
	int fd; /* file descriptor fisier */
	unsigned char buf[BUFSIZE]; /* buffer de date */
	int idx; /* indice caracter curent din buf */
	long fseek; /* cursor fisier */
	ssize_t bytesRead; /* numar bytes cititi la ultimul apel read */
	int last_op; /* READ_OP sau WRITE_OP */
	int eof; /* end of file */
	int error; /* error */
	int pid;
};

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
	SO_FILE *so_file = (SO_FILE *) calloc(1, sizeof(SO_FILE));

	if (so_file == NULL)
		return NULL;

	int fd;

	if (!strcmp(mode, "r")) {
		/* deschidere fisier pentru citire. */
		/* daca fisierul nu exista, esueaza. */
		fd = open(pathname, O_RDONLY);
		if (fd < 0) {
			free(so_file);
			return NULL;
		}

	} else if (!strcmp(mode, "r+")) {
		/* deschidere fisier pentru citire si scriere. */
		/* daca fisierul nu exista, esueaza. */
		fd = open(pathname, O_RDWR);
		if (fd < 0) {
			free(so_file);
			return NULL;
		}

	} else if (!strcmp(mode, "w")) {
		/* deschidere fisier pentru scriere. */
		/* daca nu exista, este creat. */
		/* daca exista, este trunchiat la dimensiune 0. */
		fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0) {
			free(so_file);
			return NULL;
		}

	} else if (!strcmp(mode, "w+")) {
		/* deschidere fisierul pentru citire si scriere. */
		/* daca nu exista, este creat. daca exista, este trunchiat. */
		fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0) {
			free(so_file);
			return NULL;
		}

	} else if (!strcmp(mode, "a")) {
		/* deschidere fisier in mod append, scriere la final. */
		/* daca fisierul nu exista, este creat. */
		fd = open(pathname, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0) {
			free(so_file);
			return NULL;
		}

	} else if (!strcmp(mode, "a+")) {
		/* deschidere fisier in modul append + read. */
		fd = open(pathname, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0) {
			free(so_file);
			return NULL;
		}
	} else {
		free(so_file);
		return NULL;
	}

	so_file->fd = fd;
	so_file->idx = 0;
	so_file->fseek = 0;
	so_file->bytesRead = 0;
	so_file->last_op = -1;
	so_file->error = 0; /* no error */
	so_file->eof = 0;
	so_file->pid = -1;

	return so_file;
}

int so_fclose(SO_FILE *stream)
{
	int rc;

	if (stream->last_op == WRITE_OP) {
		/* write to file */
		rc = so_fflush(stream);
		if (rc == SO_EOF) {
			/* eliberare memorie */
			rc = close(stream->fd);

			free(stream);

			return SO_EOF;
		}
	}

	rc = close(stream->fd);
	if (rc < 0) {
		/* eliberare memorie */
		free(stream);
		return SO_EOF;
	}

	free(stream);

	return 0;
}

int so_fileno(SO_FILE *stream)
{
	return stream->fd;
}

int so_fflush(SO_FILE *stream)
{
	ssize_t bytes_written;

	// printf("so_fflush_fseek: %ld\n", stream->fseek);
	// printf("so_fflush_idx: %d\n", stream->idx);
	// printf("buf: %s\n", stream->buf);

	bytes_written = xwrite(stream->fd, stream->buf, stream->idx);

	if (bytes_written <= 0) {
		stream->error = ERROR;
		return SO_EOF;
	}

	memset(stream->buf, 0, BUFSIZE);
	stream->idx = 0;
	stream->last_op = FFLUSH_OP;

	return 0;
}

int so_fseek(SO_FILE *stream, long offset, int whence)
{
	int rc;

	if (stream->last_op == READ_OP) {
		/* invalid buf */
		printf("intra aiiciii\n");
		memset(stream->buf, 0, BUFSIZE);
		stream->idx = 0;

	} else if (stream->last_op == WRITE_OP) {
		/* write to file */
		so_fflush(stream);
	}

	rc = lseek(stream->fd, offset, whence);
	if (rc < 0) {
		stream->error = ERROR;
		return SO_EOF;
	}

	stream->fseek = rc;
	stream->last_op = FSEEK_OP;

	return 0;
}

long so_ftell(SO_FILE *stream)
{
	if (stream->error == ERROR)
		return SO_EOF;

	return stream->fseek;
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	int i, c;

	for (i = 0; i < size * nmemb; i++) {
		c = so_fgetc(stream);

		/* daca am ajuns deja la final */
		if (c == SO_EOF && stream->eof)
			return i / size;

		if (stream->error == ERROR)
			return 0;

		((unsigned char *)ptr)[i] = (unsigned char)c;
	}

	return nmemb;
}

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	int i, c, ret;

	for (i = 0; i < size * nmemb; i++) {
		c = ((unsigned char *)ptr)[i];
		ret = so_fputc(c, stream);

		if (ret == SO_EOF)
			return SO_EOF;
	}

	return nmemb;
}

int so_fgetc(SO_FILE *stream)
{
	ssize_t bytes_read_now;

	/* daca vreau sa iau caracterul din buffer */
	/* dar nu il am, citesc un buffer */
	if (stream->idx == 0) {
		bytes_read_now = read(stream->fd, stream->buf, BUFSIZE);

		if (bytes_read_now == 0) {
			stream->eof = 1;
			return SO_EOF;
		}

		stream->fseek++;
		// printf("idx_0: %ld\n", bytes_read_now);
		stream->bytesRead = bytes_read_now;
		stream->idx++;
		stream->last_op = READ_OP;

		return stream->buf[0];
	}

	if (stream->idx >= 1 && stream->idx < stream->bytesRead) {
		stream->idx++;
		stream->fseek++;
		stream->last_op = READ_OP;

		return stream->buf[(stream->idx) - 1];
	}

	if (stream->idx == stream->bytesRead) {
		bytes_read_now = read(stream->fd, stream->buf, BUFSIZE);
		// printf("idx_BUFSIZE: %ld\n", bytes_read_now);

		if (bytes_read_now == 0) {
			stream->eof = 1;
			return SO_EOF;
		}

		stream->fseek++;
		stream->bytesRead = bytes_read_now;
		stream->idx = 1;
		stream->last_op = READ_OP;

		return stream->buf[0];
	}

	stream->error = ERROR;
	return SO_EOF;
}

int so_fputc(int c, SO_FILE *stream)
{
	// ssize_t byte_written;
	int ret;

	// printf("idx: %d\n", stream -> idx);

	/* daca buf nu e plin, adaug in buf caracterul c */
	if (stream->idx == BUFSIZE) {
		/* buf plin */
		stream->last_op = WRITE_OP;

		ret = so_fflush(stream);
		if (ret == SO_EOF) {
			stream->error = ERROR;
			return SO_EOF;
		}

		stream->buf[stream->idx] = c;
		stream->idx++;

		stream->fseek++;

		return c;

	} else {
		/* buf nu e plin -> adaug in el */
		stream->buf[stream->idx] = c;
		stream->idx++;

		stream->fseek++;
		stream->last_op = WRITE_OP;

		return c;
	}

	stream->error = ERROR;
	return SO_EOF;
}

int so_feof(SO_FILE *stream)
{
	return stream->eof;
}

int so_ferror(SO_FILE *stream)
{
	return stream->error;
}

SO_FILE *so_popen(const char *command, const char *type)
{
	pid_t pid;
	int fds[2];
	int rc;

	SO_FILE *so_file;
	const char *argv[] = {"sh", "-c", command, NULL};

	printf("cmd: %s\n", command);

	/* creare pipe anonim */
	rc = pipe(fds);
	if(rc < 0)
		return NULL;

	pid = fork();
	switch(pid) {

		case -1:
			/* error forking */
			close(fds[0]);
			close(fds[1]);
			return NULL;

		case 0:
			/* child */ 
			// redirectionare ??
			if(!strcmp(type, "w")) {
				close(fds[1]);	
				dup2(fds[0], STDOUT_FILENO);
			}
			else if (!strcmp(type, "r")) {
				close(fds[0]);
				dup2(fds[1], STDOUT_FILENO);
			}

			execvp("sh", (char *const *) argv);

			/* only if exec failed */
			return NULL;

		default:
			/* parent */
			if(!strcmp(type, "w")) {
				close(fds[0]);	
			} else if(!strcmp(type, "r")) {
				close(fds[1]);
			}

			so_file = (SO_FILE *) calloc(1, sizeof(SO_FILE));
			if (so_file == NULL)
				return NULL;

			if(!strcmp(type, "w")) {
				so_file->fd = fds[1];
			}
			else if(!strcmp(type, "r")) {
				so_file->fd = fds[0];
			}

			so_file->idx = 0;
			so_file->fseek = 0;
			so_file->bytesRead = 0;
			so_file->last_op = -1;
			so_file->error = 0;
			so_file->eof = 0;
			so_file->pid = pid;

			break;
	}

	/* only parent process gets here */
	return so_file;
}

int so_pclose(SO_FILE *stream)
{
	pid_t wait_ret;
	int status;

	pid_t pid = stream->pid;
	so_fclose(stream);	
	
	 wait_ret = waitpid(pid, &status, 0);

	 if(wait_ret < 0) {
	 	return SO_EOF;
	 }

	return 0;
}

