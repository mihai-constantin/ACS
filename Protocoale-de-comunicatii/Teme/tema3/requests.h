// Protocoale de comunicatii
// Tema 3
// CONSTANTIN MIHAI - 321CD

#ifndef _REQUESTS_
#define _REQUESTS_

char *compute_get_request(char *host, char *url, char *url_params, char *cookies, char *authorization);
char *compute_post_request(char *host, char *url, char *form_data, char *content_type, char *cookies, char *authorization);

#endif