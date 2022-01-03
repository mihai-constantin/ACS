// CONSTANTIN MIHAI - 321CD

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"
#include "implementare.h"

void send_file(char *buff, int number_of_packages, int window_size, int del) {
    int count_rec = 0, count_snt = 1;
    msg t, r;
    msg2 t2, r2;
    t.len = MSGSIZE;

    if (window_size > number_of_packages) {
        window_size = number_of_packages;
    }

    // trimit o rafala de pachete
    while (count_snt <= window_size) {
        memcpy(t2.payload, buff + (count_snt * MSG2SIZE), MSG2SIZE);
        t2.idx = count_snt++;
        t2.check_sum = 0;
        t2.check_sum = checksum((char *) &t2);
        memcpy(t.payload, &t2, MSGSIZE);
        send_message(&t);
    }

    while (count_rec <= number_of_packages) {
        // ne oprim la time_out
        // sau daca s-au trimis toate pachetele
        if (recv_message_timeout(&r, del / 3) < 0) {

            // timeout - retrimitem pachetul curent
            printf("[SEND] timeout\n");
            if (count_rec == 0) {
                memset(t.payload, 0, MSGSIZE);
                memcpy(&t2, buff, MSG2SIZE);
            } else {
                memcpy(t2.payload, buff + (count_rec * MSG2SIZE), MSG2SIZE);
                t2.idx = count_rec;
                t2.check_sum = 0;
                t2.check_sum = checksum((char *) &t2);
            }
            memcpy(t.payload, &t2, MSGSIZE);
            send_message(&t);
        } else {
            memcpy(&r2, r.payload, MSGSIZE);

            if (r2.check_sum == 0) {
                // am primit un ACK
                if (r2.idx >= count_rec) {
                    // am primit ACK pentru pachetul curent
                    // slide window
                    count_rec = r2.idx + 1;
                }

                // daca mai sunt pachete de trimis, trimitem urmatorul pachet
                if (count_snt <= number_of_packages) {
                    memcpy(t2.payload, buff + (count_snt * MSG2SIZE), MSG2SIZE);
                    t2.idx = count_snt++;
                    t2.check_sum = 0;
                    t2.check_sum = checksum((char *) &t2);
                    memcpy(t.payload, &t2, MSGSIZE);
                    send_message(&t);
                }
            } else {
                if (r2.idx < 0 || r2.idx > number_of_packages) {
                    continue;
                }
                // am primit NACK
                // retrimitem pachetul NACK
                if (r2.idx == 0) {
                    memset(t.payload, 0, MSGSIZE);
                    memcpy(&t2, buff, MSG2SIZE);
                } else {
                    memcpy(t2.payload, buff + (r2.idx * MSG2SIZE), MSG2SIZE);
                    t2.idx = r2.idx;
                    t2.check_sum = 0;
                    t2.check_sum = checksum((char *) &t2);
                }
                memcpy(t.payload, &t2, MSGSIZE);
                send_message(&t);
            }
        }
    }
}

int main(int argc, char **argv) {
    init(HOST, PORT1);
    msg t;
    msg2 t2;

    // setam primii MSGSIZE + 4 bytes din t la 0
    memset(&t, 0, MSGSIZE + 4);

    // setam primii MGS2SIZE bytes din t2 la 0
    memset(&t2, 0, MSG2SIZE);

    int spd = atoi(argv[2]); // viteza de transmisie
    int del = atoi(argv[3]); // timpul de propagare - delay
    int window_size = (spd * del * 1000) / (8 * sizeof(msg)); //dimensiune fereastra
    if (window_size < 0) {
        window_size = 1;
    }

    int fd = open(argv[1], O_RDONLY); // deschidre fileX
    int filesize = lseek(fd, 0, SEEK_END);
    int number_of_packages = filesize / MSG2SIZE + 1; // numar pachete
    lseek(fd, 0, SEEK_SET);
    char *buff = (char *) malloc(filesize + MSG2SIZE); // buffer unde citesc
    if (read(fd, buff + MSG2SIZE, filesize) < 0) {
        printf("[SEND] File read error. Exiting\n");
        free(buff);
        return -1;
    }
    close(fd);

    t2.idx = 0;
    memcpy(t2.payload, &filesize, sizeof(int));
    strcpy(t2.payload + 4, argv[1]);
    t2.check_sum = checksum((char *) &t2);
    memcpy(t.payload, &t2, MSGSIZE);
    t.len = MSGSIZE; // MSGSIZE = 1400

    // salvam filesize si filename ca primul frame
    memcpy(buff, &t2, MSG2SIZE);

    // crestem numarul de pachete
    number_of_packages++;

    // send filename
    send_message(&t);
    // send file
    send_file(buff, number_of_packages, window_size, del);
    printf("[SEND] finished\n");

    // received message
    recv_message(&t);

    return 0;
}
