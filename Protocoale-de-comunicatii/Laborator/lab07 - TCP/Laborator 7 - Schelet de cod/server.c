/*
 * Protocoale de comunicatii
 * Laborator 7 - TCP
 * Echo Server
 * server.c
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    int listenfd = 0, sockfd = 0;
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

    // legare proprietati de socket
    bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr));

    // ascultare de conexiuni
    listenfd = listen(sockfd, 3);

    srand(time(NULL));

    // acceptarea unei conexiuni, primirea datelor, trimiterea raspunsului
    int s1 = 0, r;
    unsigned int len = sizeof(struct sockaddr);
    while(1) {
        s1 = accept(sockfd, (struct sockaddr*) &serv_addr, &len);

        while(1) {
            recv(s1, buf, BUFLEN, 0);
            printf("primire buf server: %s\n", buf);
            r = rand();     
            if(r & 1) {
                send(s1, "yes", BUFLEN, 0);
            }
            else {
                send(s1, "no", BUFLEN, 0);
            }
        }
        
        // inchidere conexiune cu clientul
        close(s1);
    }

    // inchidere server
    close(sockfd);

    return 0;
}
