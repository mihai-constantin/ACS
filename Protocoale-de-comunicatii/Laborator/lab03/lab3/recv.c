#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001

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
  msg r,t;
  init(HOST,PORT);

  if (recv_message(&r)<0){
    perror("Receive message");
    return -1;
  }

  printf("[%s] Got msg with payload: %s\n",argv[0],r.payload);

  sprintf(t.payload,"ACK");
  t.len = strlen(t.payload+1);
  send_message(&t);
  return 0;
}
