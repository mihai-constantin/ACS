// CONSTANTIN MIHAI - 321CD

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"
#include "implementare.h"

void recv_file(char *buff, char **filename, int *filesize) {
    int count_rec = 0, last_package = -10;
    int number_of_packages = MAXWINDOWSIZE;
    msg r;
    msg2 r2;
    *filename = calloc(MSG2SIZE, sizeof(char));
    memset(&r, 0, MSGSIZE + 4);
    memset(&r2, 0, MSGSIZE);
    char *packages_received = calloc(MAXWINDOWSIZE, sizeof(char));

    while (count_rec <= number_of_packages) {
        recv_message(&r);
        memcpy(&r2, r.payload, MSGSIZE);

        if (checksum((char *) &r2) != 0) {
            // am primit un pachet corupt
            // trebuie sa retrimitem pachetul
            r2.check_sum = 1;
            memcpy(r.payload, &r2, MSGSIZE);
            send_message(&r);

            continue;
        }

        // am primit un pachet corect
        // copiem continutul in buffer
        if (r2.idx == 0) {
            // am primit primul pachet
            memcpy(filesize, r2.payload, sizeof(4));
            number_of_packages = (*filesize) / MSG2SIZE + 2;
            sprintf(*filename, "recv_%s", r2.payload + 4);
        } else {
            memcpy(buff + (r2.idx * MSG2SIZE), r2.payload, MSG2SIZE);
        }

        packages_received[r2.idx] = 1;

        if (r2.idx == count_rec) {
            // am primit pachetul asteptat
            // trimitem ACK
            r2.check_sum = 0;
            memcpy(r.payload, &r2, MSGSIZE);
            send_message(&r);

            count_rec++;
            if (last_package != -10) {
                last_package = -10;
                // check the buffered packages
                while (count_rec <= number_of_packages && packages_received[count_rec] == 1) {
                    count_rec++;
                }
                if (count_rec > number_of_packages) {
                    r2.check_sum = 0;
                    r2.idx = count_rec;
                    memcpy(r.payload, &r2, MSGSIZE);
                    send_message(&r);
                }
            }
        } else {
            // am primit un alt pachet decat cel asteptat
            if (last_package == -10) {
                // trimitem NACK pentru ultimul pachet confirmat
                last_package = count_rec - 1;
                r2.idx = count_rec;
                r2.check_sum = 1;
                memcpy(r.payload, &r2, MSGSIZE);
                send_message(&r);
            } else {
                // trimitem ACK pentru ultimul pachet confirmat
                r2.idx = last_package;
                r2.check_sum = 0;
                memcpy(r.payload, &r2, MSGSIZE);
                send_message(&r);
            }
        }
    }

    free(packages_received);
}

int main(int argc, char **argv) {
    msg t;
    int filesize, fd;
    char *filename;
    char *buff = malloc(MAXWINDOWSIZE * MSGSIZE);
    init(HOST, PORT2);

    recv_file(buff, &filename, &filesize);
    printf("[RECV] finished\n");

    // deschidere fisier
    fd = open(filename, O_WRONLY | O_CREAT, 0644);

    // write the file
    write(fd, buff + MSG2SIZE, filesize);

    // trimitere mesaj
    send_message(&t);

    // close file
    close(fd);
    free(filename);

    return 0;
}
