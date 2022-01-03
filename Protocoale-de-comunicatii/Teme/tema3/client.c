// Protocoale de comunicatii
// Tema 3
// CONSTANTIN MIHAI - 321CD

#include <stdio.h>      /* fprintf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include <json-c/json.h>
#include "helpers.h"
#include "requests.h"

// get a buffer with cookies
char* getCookies(char *response) {

    char *ret;
    const char *delims = "\r\n";
    char *word = strtok(response, delims);
    char *sol = (char*) calloc(BUFLEN, sizeof(char));

    while(word != NULL) {
        ret = strstr(word, "Set-Cookie:");
        if(ret != NULL) {
            strcat(sol, word + 12);
            strcat(sol, "; ");
        }
    
        word = strtok(NULL, delims);
    }

    int length = strlen(sol);
    sol[length - 1] = 0;
    sol[length - 2] = 0;

    return sol;
}

// receives a name and prints IP address
char* get_ip(const char *name) {

    struct addrinfo hints, *result, *p;
    char *res = (char*) malloc(BUFLEN * sizeof(char));

    // set hints
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;

    // get address
    getaddrinfo(name, "http", &hints, &result);

    p = result;
    inet_ntop(p -> ai_family, &(((struct sockaddr_in *) (p -> ai_addr)) -> sin_addr), res, BUFLEN);

    freeaddrinfo(result);

    return res;
}

int main(int argc, char *argv[])
{
    int sockfd;
    char *message;
    char *response;

    /*
     *  TASK 1
     */

    // se deschide conexiunea (open_connection)
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);

    // se creaza mesajul de request (compute_get_request)
    message = compute_get_request(IP_SERVER, "/task1/start", NULL, NULL, NULL);
    printf("=====     TASK 1 - SEND     =====\n");
    printf("%s", message);

    // se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);

    // se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("=====     TASK 1 - RECEIVE     =====\n");
    printf("%s\n", response);
    printf("\n");

    // se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    /*
     *  TASK 2
     */

    char *body;
    body = strchr(response, '{');

    struct json_object *parsed_json;
    struct json_object *enunt;
    struct json_object *url;
    struct json_object *method;
    struct json_object *type;

    parsed_json = json_tokener_parse(body);
    json_object_object_get_ex(parsed_json, "enunt", &enunt);
    json_object_object_get_ex(parsed_json, "url", &url);
    json_object_object_get_ex(parsed_json, "method", &method);
    json_object_object_get_ex(parsed_json, "type", &type);

    char *data;
    data = strstr(response, "\"data\"");    

    struct json_object *parsed_data;
    struct json_object *username;
    struct json_object *password;

    parsed_data = json_tokener_parse(data + 7);
    json_object_object_get_ex(parsed_data, "username", &username);
    json_object_object_get_ex(parsed_data, "password", &password);

    // se deschide conexiunea (open_connection)
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);

    // formare login
    char *login = (char*) calloc(BUFLEN, sizeof(char));
    strcpy(login, "username=");
    strcat(login, json_object_get_string(username));
    strcat(login, "&password=");
    strcat(login, json_object_get_string(password));

    const char *URL = json_object_get_string(url);
    const char *TYPE = json_object_get_string(type);
    const char *METHOD = json_object_get_string(method);

    // formare cookies
    char *cookies = getCookies(response);

    // se creaza mesajul de request
    if(strcmp(METHOD, "POST") == 0) {
        message = compute_post_request(IP_SERVER, (char*) URL, login, (char *) TYPE, cookies, NULL);
    }
    else {
        message = compute_get_request(IP_SERVER, (char*) URL, NULL, cookies, NULL);
    }
    printf("=====     TASK 2 - SEND     =====\n");
    printf("%s\n", message);

    // se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);

    // se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("=====     TASK 2 - RECEIVE     =====\n");
    printf("%s\n", response);
    printf("\n");

    // se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    /*
     *  TASK 3
     */

    body = strchr(response, '{');

    parsed_json = json_tokener_parse(body);
    json_object_object_get_ex(parsed_json, "enunt", &enunt);
    json_object_object_get_ex(parsed_json, "url", &url);
    json_object_object_get_ex(parsed_json, "method", &method);

    data = strstr(response, "\"data\"");  

    struct json_object *token;
    struct json_object *queryParams;

    parsed_data = json_tokener_parse(data + 7);
    json_object_object_get_ex(parsed_data, "token", &token);
    json_object_object_get_ex(parsed_data, "queryParams", &queryParams);

    // se deschide conexiunea (open_connection)
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);

    // formare cookies
    cookies = getCookies(response);

    // get URL
    URL = json_object_get_string(url);

    const char *QUERY = json_object_get_string(queryParams);
    struct json_object *parse_query;
    struct json_object *id;

    parse_query = json_tokener_parse(QUERY);
    json_object_object_get_ex(parse_query, "id", &id);

    char *answer = (char *) calloc(BUFLEN, sizeof(char));
    strcpy(answer, "raspuns1=omul&raspuns2=numele&id=");
    strcat(answer, json_object_get_string(id));

    const char *authorization = json_object_get_string(token);
    METHOD = json_object_get_string(method);

    // se creaza mesajul de request
    if(strcmp(METHOD, "GET") == 0) {
        message = compute_get_request(IP_SERVER, (char*) URL, answer, cookies, (char*) authorization);
    }
    else {
        message = compute_post_request(IP_SERVER, (char*) URL, answer, (char*) TYPE, cookies, (char*) authorization);
    }

    printf("=====     TASK 3 - SEND     =====\n");
    printf("%s", message);

    // se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);

    // se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("=====     TASK 3 - RECEIVE     =====\n");
    printf("%s\n", response);
    printf("\n");

    // se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    /*
     *  TASK 4
     */
    body = strchr(response, '{');

    parsed_json = json_tokener_parse(body);
    json_object_object_get_ex(parsed_json, "enunt", &enunt);
    json_object_object_get_ex(parsed_json, "url", &url);
    json_object_object_get_ex(parsed_json, "method", &method);

    // se deschide conexiunea (open_connection)
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);

    // get URL
    URL = json_object_get_string(url);

    // get METHOD
    METHOD = json_object_get_string(method);

    // formare cookies
    cookies = getCookies(response);

    // se creaza mesajul de request
    if(strcmp(METHOD, "GET") == 0) {
        message = compute_get_request(IP_SERVER, (char *) URL, NULL, cookies, (char *) authorization);
    }
    else {
        message = compute_post_request(IP_SERVER, (char *) URL, NULL, (char *) TYPE, cookies, (char *) authorization);
    }

    printf("=====     TASK 4 - SEND     =====\n");
    printf("%s", message);

    // se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);

    // se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("=====     TASK 4 - RECEIVE     =====\n");
    printf("%s\n", response);
    printf("\n");

    char *response2 = (char*) malloc(BUFLEN * sizeof(char));
    strcpy(response2, response);

    // se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    /* 
     * TASK 5.1 - GET IP
     */

    body = strchr(response, '{');
    parsed_json = json_tokener_parse(body);
    json_object_object_get_ex(parsed_json, "enunt", &enunt);
    json_object_object_get_ex(parsed_json, "url", &url);
    json_object_object_get_ex(parsed_json, "method", &method);
    json_object_object_get_ex(parsed_json, "type", &type);

    data = strstr(response, "\"data\"");  

    struct json_object *url_data;
    struct json_object *method_data;

    parsed_data = json_tokener_parse(data + 7);
    json_object_object_get_ex(parsed_data, "url", &url_data);
    json_object_object_get_ex(parsed_data, "queryParams", &queryParams);
    json_object_object_get_ex(parsed_data, "method", &method_data);

    QUERY = json_object_get_string(queryParams);
    parse_query = json_tokener_parse(QUERY);

    struct json_object *q;
    struct json_object *APPID;

    json_object_object_get_ex(parse_query, "q", &q);
    json_object_object_get_ex(parse_query, "APPID", &APPID);

    const char *delims = "/";
    const char *URL_DATA = json_object_get_string(url_data);
    char *word = strtok((char*) URL_DATA, delims);  

    char *url_weather = (char*) calloc(BUFLEN, sizeof(char));
    strcpy(url_weather, "/");
    while(word != NULL) {
        word = strtok(NULL, delims);
        if(word != NULL) {
            strcat(url_weather, word);
            strcat(url_weather, "/");
        }
    }

    int length = strlen(url_weather);
    url_weather[length - 1] = 0;

    // formare login
    char *url_params = (char*) calloc(BUFLEN, sizeof(char));
    strcpy(url_params, "q=");
    strcat(url_params, json_object_get_string(q));
    strcat(url_params, "&APPID=");
    strcat(url_params, json_object_get_string(APPID));

    word = strtok((char*) URL_DATA, delims);
    
    char *ip_weather = get_ip(word);

    printf("=====     TASK 5 - DOMAIN NAME AND IP ADDRESS     =====\n");
    printf("%s : %s\n", word, ip_weather);  
    printf("\n");

    /* 
     *  TASK 5.2 - GET
     */

    // se deschide conexiunea (open_connection)
    sockfd = open_connection(ip_weather, 80, AF_INET, SOCK_STREAM, 0);

    // get method
    METHOD = json_object_get_string(method);

    // se creaza mesajul de request
    message = compute_get_request(ip_weather, url_weather, url_params, NULL, NULL);

    printf("=====     TASK 5 - SEND_1     =====\n");
    printf("%s", message);

    // se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);

    // se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("=====     TASK 5 - RECEIVE_1     =====\n");
    printf("%s\n", response);
    printf("\n");

    // se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    /* 
     *  TASK 5.3 - POST
     */
    char *body2 = strchr(response, '{');

    body = strchr(response2, '{');
    parsed_json = json_tokener_parse(body);
    json_object_object_get_ex(parsed_json, "enunt", &enunt);
    json_object_object_get_ex(parsed_json, "url", &url);
    json_object_object_get_ex(parsed_json, "method", &method);
    json_object_object_get_ex(parsed_json, "type", &type);

    // se deschide conexiunea (open_connection)
    sockfd = open_connection(IP_SERVER, PORT_SERVER, AF_INET, SOCK_STREAM, 0);

    URL = json_object_get_string(url);
    TYPE = json_object_get_string(type);

    char *finalCookies = getCookies(response2);

     // se creaza mesajul de request
    if(strcmp(METHOD, "POST") == 0) {
        message = compute_post_request(IP_SERVER, (char*) URL, body2, (char *) TYPE, finalCookies, (char *) authorization);
    }
    else {
        message = compute_get_request(IP_SERVER, (char*) URL, body2, finalCookies, (char *) authorization);
    }

    printf("=====     TASK 5 - SEND_2     =====\n");
    printf("%s", message);

    // se trimite la server mesajul (send_to_server)
    send_to_server(sockfd, message);

    // se primeste raspuns de la server (receive_from_server)
    response = receive_from_server(sockfd);
    printf("=====     TASK 5 - RECEIVE_2     =====\n");
    printf("%s\n", response);

    // se inchide conexiunea cu serverul (close_connection)
    close_connection(sockfd);

    free(message);

    return 0;
}