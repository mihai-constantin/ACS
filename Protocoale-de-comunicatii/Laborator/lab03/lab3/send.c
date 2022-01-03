#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int bit1[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21};
int bit2[] = {2, 3, 6, 7, 10, 11, 14, 15, 18, 19};
int bit4[] = {4, 5, 6, 7, 12, 13, 14, 15, 20, 21};
int bit8[] = {8, 9, 10, 11, 12, 13, 14, 15};
int bit16[] = {16, 17, 18, 19, 20, 21};


int getBit(char c, int pos) {
	return (c >> (8 - pos)) % 2;
}

char setBit(char c, int pos) {
	return (c | (1 << (8 - pos)));
}

char unsetBit(char c, int pos) {
	return c & (~(1<<(8 - pos)));
}

int main(int argc,char** argv) {
  init(HOST,PORT);
  msg t;

  // sprintf(t.payload,"Hello World of PC");
  // t.len = strlen(t.payload)+1;
  // send_message(&t);

  t.payload[0] = 0;
  t.payload[1] = 0;
  t.payload[2] = '\0';
  t.len = 3;

  int s1, s2, s4, s8;
  char* message = "Ana are mere";
  for(int i = 0; i < strlen(message); i++) {

  	for(int pos = 1; pos <= 8; pos++) {
  		if(pos == 1 && getBit(message[i], pos) == 1) {
  			t.payload[0] = setBit(t.payload[0], (pos + 2));
  		}
  		else{
  			if(pos >= 2 && pos <= 4 && getBit(message[i], pos) == 1) {
  				t.payload[0] = setBit(t.payload[0], (pos + 3));	
  			}
  			else{
  				if(pos >= 5 && getBit(message[i], pos) == 1) {
  					t.payload[1] = setBit(t.payload[0], (pos - 4));	
  				}
  			}
  		}

  		s1 = getBit(t.payload[0], 3) + getBit(t.payload[0], 5)
               + getBit(t.payload[0], 7) + getBit(t.payload[1], 1)
               + getBit(t.payload[1], 3);

    	s2 = getBit(t.payload[0], 3) + getBit(t.payload[0], 6)
               + getBit(t.payload[0], 7) + getBit(t.payload[1], 2)
               + getBit(t.payload[1], 3);

    	s4 = getBit(t.payload[0], 5) + getBit(t.payload[0], 6)
               + getBit(t.payload[0], 7) + getBit(t.payload[1], 4);

    	s8 = getBit(t.payload[1], 1) + getBit(t.payload[1], 2)
               + getBit(t.payload[1], 3) + getBit(t.payload[1], 4);

        if(s1 % 2){
			setBit(t.payload[0], 1);
		}
		if(s2 % 2){
			setBit(t.payload[0], 2);
		}
		if(s4 % 2){
			setBit(t.payload[0], 4);
		}
		if(s8 % 2){
			setBit(t.payload[0], 8);
		}
  	}

  	send_message(&t);
  	if (recv_message(&t)<0){
    	perror("receive error");
 	}
  	else {
    	printf("[%s] Got reply with payload: %s\n",argv[0],t.payload);
  	}
  }

  

  return 0;
}
