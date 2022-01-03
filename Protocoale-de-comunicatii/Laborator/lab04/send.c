#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc, char *argv[])
{
	msg t;
	int i, res;
	
	printf("[SENDER] Starting.\n");	
	init(HOST, PORT);

	int df = atoi(argv[1]) / (MSGSIZE * 8);
	printf("[SENDER]: DF=%d\n", df); 
	printf("[SENDER]: BDP=%d\n", atoi(argv[1])); 

	/* cleanup msg */
	memset(&t, 0, sizeof(msg));
		
	/* gonna send an empty msg */
	t.len = MSGSIZE;

	for(i = 0; i < df; i++) {
		/* send msg */
		sprintf(t.payload, "trash");
		t.len = strlen(t.payload) + 1;
		res = send_message(&t);
		if (res < 0) {
			perror("[SENDER] Send error. Exiting.\n");
			return -1;
		}
		printf("SENT MESSAGE %s\n", t.payload);
	}

	for(i = 0; i < (COUNT - df); i++) {
		/* wait for ACK */
		res = recv_message(&t);
		if (res < 0) {
			perror("[SENDER] Receive error. Exiting.\n");
			return -1;
		}

		printf("RECEIVED ACK %d\n", i);

		/* send msg */
		res = send_message(&t);
		if (res < 0) {
			perror("[SENDER] Send error. Exiting.\n");
			return -1;
		}
		printf("SENT MESSAGE %d\n", i);
	}

	for(i = 0; i < df; i++) {
		/* wait for ACK */
		res = recv_message(&t);
		if (res < 0) {
			perror("[SENDER] Receive error. Exiting.\n");
			return -1;
		}
	}

	printf("[SENDER] Job done, all sent.\n");

	// for (i = 0; i < COUNT; i++) {
		// /* cleanup msg */
		// memset(&t, 0, sizeof(msg));
		
		// /* gonna send an empty msg */
		// t.len = MSGSIZE;
		
	// 	/* send msg */
	// 	res = send_message(&t);
	// 	if (res < 0) {
	// 		perror("[SENDER] Send error. Exiting.\n");
	// 		return -1;
	// 	}
		
	// 	/* wait for ACK */
	// 	res = recv_message(&t);
	// 	if (res < 0) {
	// 		perror("[SENDER] Receive error. Exiting.\n");
	// 		return -1;
	// 	}
	// }

	// printf("[SENDER] Job done, all sent.\n");
		
	return 0;
}
