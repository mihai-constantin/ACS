/*
 * Protocoale de comunicatii:
 * Laborator 6: UDP
 * mini-server de backup fisiere
 */
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "helpers.h"


void usage(char*file)
{
	fprintf(stderr, "Usage: %s server_port file\n", file);
	exit(0);
}

/*
 * Utilizare: ./server server_port nume_fisier
 */
int main(int argc, char **argv)
{
	if (argc != 3)
		usage(argv[0]);

	int fd, ret;
	socklen_t socklen;
	struct sockaddr_in from_station;
	char buf[BUFLEN];

	/* TODO deschidere socket */
	fd = socket(PF_INET, SOCK_DGRAM, 0);

	/* TODO setare struct sockaddr_in pentru a specifica unde trimit
	 * datele */
	from_station.sin_family = AF_INET;
	from_station.sin_port = htons(atoi(argv[1]));

	/* TODO legare proprietăți de socket */
	bind(fd, (struct sockaddr*) &from_station, sizeof(struct sockaddr));

	/* TODO deschidere fișier pentru scriere */
	ret = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT);
	DIE(ret == -1, "open failed");

	/*
	 * TODO
	 * cat_timp  mai_pot_citi
	 *		citeste din socket
	 *		pune in fisier
	 */

	socklen = sizeof(struct sockaddr);
	int nbytes;
	while((nbytes = recvfrom(fd, buf, BUFLEN, 0, (struct sockaddr*) &from_station, &socklen))) {
		write(ret, buf, nbytes);
	}

	/* TODO închidere socket */
	close(fd);

	/* TODO închidere fișier */
	close(ret);

	return 0;
}
