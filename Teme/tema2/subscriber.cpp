// Protocoale de comunicatii
// Tema 2
// Constantin Mihai - 321CD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <netinet/tcp.h>
#include "helper.h"

#include <iostream>
#include <iterator>
#include <unordered_map>

using namespace std;

/*
 * Utilizare: ./subscriber id_client ip_server server_port
 */

char buffer[BUFLEN];
char id_client[BUFLEN];

char topic[BUFLEN];

void writeMessageToConsole() {
	
	unsigned int j, space_pos = 0;

	// subscribe
	if(strncmp(buffer, "subscribe", 9) == 0) {
		strcpy(topic, buffer + 10);
	
		// space_pos -> unde se termina topic-ul
		for(j = 0; j < strlen(topic); j++) {
			if(topic[j] == ' ') {	
				space_pos = j;
				break;
			}
		}
	
		memset(topic, 0, BUFLEN);
		for(j = 0; j < space_pos; j++) {
			topic[j] = buffer[j + 10];
		}

		printf("subscribed %s\n", topic);
	}
	else {
		if(strncmp(buffer, "unsubscribe", 11) == 0) {
			// unsubscribe
			strcpy(topic, buffer + 12);
		
			space_pos = strlen(topic) - 1;

			// unsubscribe - formare topic
			memset(topic, 0, BUFLEN);
			for(j = 0; j < space_pos; j++) {
				topic[j] = buffer[j + 12];
			}
			printf("unsubscribed %s\n", topic);
		}
	}

}

void usage(char *file)
{
	fprintf(stderr, "Usage: %s <id_client> <ip_server> <server_port>\n", file);
	exit(0);
}

int main(int argc, char *argv[])
{

	if (argc != 4){
		usage(argv[0]);
	}

	int sockfd, ret, n, fdmax;
	struct sockaddr_in serv_addr;

	// creare socket TCP
	int domain = AF_INET;
	int type = SOCK_STREAM;
	int protocol = 0;

	sockfd = socket(domain, type, protocol);
	DIE(sockfd < 0, "socket");

	// setare struct sockaddr_in pentru a specifica unde trimit datele
	serv_addr.sin_family = domain;
	serv_addr.sin_port = htons(atoi(argv[3]));
	ret = inet_aton(argv[2], &serv_addr.sin_addr);
	DIE(ret == 0, "inet_aton");

	socklen_t socklen = sizeof(struct sockaddr);
	ret = connect(sockfd, (struct sockaddr*) &serv_addr, socklen);
	DIE(ret < 0, "connect");

	fd_set read_fds; // multimea de citire folosita in select()
	fd_set tmp_fds; // multimea folosita temporar

	// se goleste multimea de descriptori de citire (read_fds)
	// si multimea temporara (tmp_fds)
	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	// se adauga in multimea descriptorilor de citire socketul TCP
	FD_SET(sockfd, &read_fds);
	// setare fdmax
	fdmax = sockfd;

	FD_SET(0, &read_fds); // stdin

	// trimitere id_client catre server
	strcpy(id_client, argv[1]);
	send(sockfd, id_client, sizeof(id_client), 0);

	// dezactivarea algoritmului Neagle
	// toate comenzile si mesajele trimise in platforma isi vor produce
	// efectul imediat
	int flag = 1;
	setsockopt(sockfd,            /* socket affected */
                IPPROTO_TCP,     /* set option at TCP level */
                TCP_NODELAY,     /* name of option */
                (char *) &flag,  /* the cast is historical cruft */
                sizeof(int));    /* length of option value */

	while(1) {
		tmp_fds = read_fds;

		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		if(FD_ISSET(0, &tmp_fds)) {
			// se citeste de la tastatura
			memset(buffer, 0, BUFLEN);
			fgets(buffer, BUFLEN - 1, stdin);

			// inchidere client
			if(strncmp(buffer, "exit", 4) == 0) {
				break;
			}

			// subscribe sau unsubscribe + verificare corectitudine comanda
			if((!strncmp(buffer, "subscribe", 9) && buffer[9] == ' ') || 
				(!strncmp(buffer, "unsubscribe", 11) && buffer[11] == ' ')) {
				// se trimite mesajul la server
				n = send(sockfd, buffer, sizeof(buffer), 0);
				DIE(n < 0, "send");

				/*
	 			* Afisare la consola a unui mesaj corespunzator.
				*/
				writeMessageToConsole();
			}
			else {
				// comanda subscriber-ului a fost introdusa eronat
				// afisam un mesaj corespunzator
				printf("Usage: subscribe <topic> <SF>\n");
				printf("Usage: unsubscribe <topic>\n");
			}
		}
		else {
			if(FD_ISSET(sockfd, &tmp_fds)) {
				memset(buffer, 0, BUFLEN);
				n = recv(sockfd, buffer, sizeof(buffer), 0);
				DIE(n < 0, "recv");

				if(n == 0) {
					printf("Server disconnected.\n");
					break;
				}
				else {
					printf("%s\n", buffer);
				}
			}
		}
	}

	// inchidere socket
	close(sockfd);

	return 0;
}