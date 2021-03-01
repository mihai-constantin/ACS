#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

int main(int argc, char *argv[])
{
    int i;
    char *message;
    char *response;
    int sockfd;

    
    /*
    *   Ex 0: Get cs.curs.pub.ro
    *   
    *   Pas 1: Se deschide conexiunea (open_connection)
    *   Pas 2: Se creaza mesajul de request (compute_get_request)
    *   Pas 3: Se trimite la server mesajul (send_to_server)
    *   Pas 4: Se primeste raspuns de la server (receive_from_server)
    *   Pas 5: Se inchide conexiunea cu serverul (close_connection)
    */

    //TODO EX 0

    /*
        Ex 1: Get videos
    */

    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    // message = compute_post_request(IP_SERVER, "/videos", "id=22&name=Nu va mai certati");
    message = compute_get_request(IP_SERVER, "/videos", NULL);

    printf("MSG: %s\n", message);

    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("RESPONSE: %s\n", response);
    close_connection(sockfd);
    
    // TODO EX 1

    /*
        EX 2.1: Add video
    */
    
    // TODO Ex 2.1

     /*
        Ex 2.2 Verificam noua colectie de videoclipuri
    */

    // TODO Ex 2.2
    
    /*
        Ex 3 Autentificare
    */

    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);
    message = compute_post_request(IP_SERVER, "/weather/login", "username=admin&password=p@ss");
    printf("MSG: %s\n", message);

    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("RESPONSE: %s\n", response);
    close_connection(sockfd);

    // TODO Ex 3

    free(message);
    return 0;
}