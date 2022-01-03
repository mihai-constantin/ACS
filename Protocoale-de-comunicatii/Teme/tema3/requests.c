// Protocoale de comunicatii
// Tema 3
// CONSTANTIN MIHAI - 321CD

#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

char *compute_get_request(char *host, char *url, char *url_params, char *cookies, char *authorization) {

    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    
    // scriem numele metodei, calea, parametri din url (daca exista) si tipul protocolului
    if (url_params != NULL){
        sprintf(line, "GET %s?%s HTTP/1.1", url, url_params);
    }
    else{
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);

    // adaugam host-ul
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // TODO: adaugam headere si/ sau cookies, respectand forma protocolului
    if(cookies != NULL) {
        sprintf(line, "Cookie: %s", cookies);
        compute_message(message, line);
    }
    
    if(authorization != NULL) {
        sprintf(line, "Authorization: Bearer %s", authorization);
        compute_message(message, line);
    }
   
    // adaugam linia de final
    compute_message(message, "");

    return message;
}

char *compute_post_request(char *host, char *url, char *form_data, char *content_type, char *cookies, char *authorization) {

    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
    
    // scriem numele metodei, calea si tipul protocolului
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    // adaugam host-ul
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // adaugare cookies
    if(cookies != NULL) {
        sprintf(line, "Cookie: %s", cookies);
        compute_message(message, line);
    }
    
    if(authorization != NULL) {
        sprintf(line, "Authorization: Bearer %s", authorization);
        compute_message(message, line);
    }

    // Content-Type & Content-Length
    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);

    sprintf(line, "Content-Length: %ld", strlen(form_data));
    compute_message(message, line);

    // adaugam linia de final de antent
    compute_message(message, "");

    // adaugam data
    sprintf(line, "%s", form_data);
    compute_message(message, line);

    return message;
}