/*
 * Protocoale de comunicatii:
 * Laborator 6: UDP
 * client mini-server de backup fisiere
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


void usage(char *file)
{
	fprintf(stderr, "Usage: %s ip_server port_server file\n", file);
	exit(0);
}

/*
 * Utilizare: ./client ip_server port_server nume_fisier_trimis
 */
int main(int argc, char **argv)
{
	if (argc != 4)
		usage(argv[0]);

	int fd, ret;
	struct sockaddr_in to_station;
	char buf[BUFLEN];

	/* TODO deschidere socket */
	fd = socket(PF_INET, SOCK_DGRAM, 0);

	/* TODO setare struct sockaddr_in pentru a specifica unde trimit
	 * datele */
	to_station.sin_family = AF_INET;
	to_station.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1], &to_station.sin_addr);

	/* TODO deschidere fișier pentru citire */
	ret = open(argv[3], O_RDONLY);
	DIE(ret == -1, "open failed");

	/*
	 * TODO
	 * cat_timp  mai_pot_citi
	 *		citeste din fisier
	 *		trimite pe socket
	 */

	int nbytes;
	while((nbytes = read(ret, buf, sizeof(buf)))) {
		sendto(fd, buf, nbytes, 0, (struct sockaddr*) &to_station, sizeof(struct sockaddr));
	}

	/* TODO închidere socket */
	close(fd);

	/* TODO închidere fișier */
	close(ret);

	return 0;
}
