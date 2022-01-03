// CONSTANTIN MIHAI -321CD

#ifndef IMPLEMENTARE
#define IMPLEMENTARE

#define MAXWINDOWSIZE 1000 // window maxim de 1000
#define MSG2SIZE 1395

// xor pe tot payload-ul
char checksum(const char *payload) {
    char check = 0;
    int i;
    for (i = 0; i < 1400; i++)
        check = check ^ payload[i];
    return check;
}

/**
 * structura msg2 cu sizeof 1400 bytes
 * idx - 4 bytes
 * check_sum - 1 byte
 * payload - MSG2SIZE = 1395 bytes
 */
#pragma pack(push, 1)
typedef struct {
    int idx;
    char check_sum;
    char payload[MSG2SIZE];
} msg2;
#pragma pack(pop)

#endif