// Protocoale de comunicatii
// Laborator 9 - DNS
// dns.c

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int usage(char* name)
{
	printf("Usage:\n\t%s -n <NAME>\n\t%s -a <IP>\n", name, name);
	return 1;
}

// Receives a name and prints IP addresses
void get_ip(char* name)
{
	int ret;
	struct addrinfo hints, *result, *p;
	char res[2048];

	// TODO: set hints
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;

	// TODO: get addresses
	getaddrinfo(name, "http", &hints, &result);

	// TODO: iterate through addresses and print them
	p = result;
	while(p != NULL) {
		inet_ntop(p -> ai_family, &(((struct sockaddr_in *) (p -> ai_addr)) -> sin_addr), res, sizeof(res));
		printf("%s\n", res);
		p = p -> ai_next;
	}

	// TODO: free allocated data
	freeaddrinfo(result);
}

// Receives an address and prints the associated name and service
void get_name(char* ip)
{
	int ret;
	struct sockaddr_in addr;
	char host[1024];
	char service[20];

	// TODO: fill in address data
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	ret = inet_aton(ip, &addr.sin_addr);

	// TODO: get name and service

	getnameinfo((struct sockaddr*) &addr, sizeof(addr), host, sizeof(host), service, sizeof(service), 0);

	// TODO: print name and service
	printf("host: %s\n", host);
	printf("service: %s\n", service);

}

int main(int argc, char **argv)
{
	if (argc < 3) {
		return usage(argv[0]);
	}

	if (strncmp(argv[1], "-n", 2) == 0) {
		get_ip(argv[2]);
	} else if (strncmp(argv[1], "-a", 2) == 0) {
		get_name(argv[2]);
	} else {
		return usage(argv[0]);
	}

	return 0;
}
