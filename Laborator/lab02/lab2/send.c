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

int main(int argc,char** argv){
  init(HOST,PORT);
  msg t;

  // sprintf(t.payload,"Hello World of PC");

  int ok = 1;

  int fd = open("file.in", O_RDONLY);
  while(1){
    memset(t.payload, 0, strlen(t.payload));
    int numberOfBytes = read(fd, t.payload, 7);

    if(numberOfBytes == 0){
      break;
    }

    if(ok == 1){
      t.payload[7] = '0';
      ok = 0;
    }
    else{
      t.payload[7] = '1';
      ok = 1;
    }
    

    t.len = strlen(t.payload)+1;
    send_message(&t);

    if (recv_message(&t)<0){
      perror("receive error");
    }
    else {
      printf("[%s] Got reply with payload: %s\n",argv[0],t.payload);
    }
  }

  t.len = strlen(t.payload)+1;
  send_message(&t);

  if (recv_message(&t)<0){
    perror("receive error");
  }
  else {
    printf("[%s] Got reply with payload: %s\n",argv[0],t.payload);
  }

  close(fd);
  return 0;
}
