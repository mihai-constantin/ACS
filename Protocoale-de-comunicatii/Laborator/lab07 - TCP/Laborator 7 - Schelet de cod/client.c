/*
 * Protocoale de comunicatii
 * Laborator 7 - TCP
 * Echo Server
 * client.c
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    int sockfd = 0, connfd = 0;
    char buf[BUFLEN];
    struct sockaddr_in serv_addr; 

    if(argc != 3)
    {
        printf("\n Usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    // deschidere socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // completare informatii despre adresa serverului
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &serv_addr.sin_addr);

    // conectare la server
    connfd = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr));

    int nbytes;
    // citire de la tastatura, trimitere de cereri catre server, asteptare raspuns
    while(1) {
        printf("citire buf client: ");
        scanf("%s", buf);
        nbytes = send(sockfd, buf, BUFLEN, 0);

        recv(sockfd, buf, BUFLEN, 0);
        printf("primire buf client: %s\n", buf);

    }

    // inchidere socket
    close(sockfd);

    return 0;
}
