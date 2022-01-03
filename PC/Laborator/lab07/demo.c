/**
 * Demo lucru cu masti
 */
#include <stdio.h>

int is_set(u_int8_t byte, int i) {
    int mask = (1 << i);
    return (byte & mask) != 0;
}
 
u_int8_t set(u_int8_t byte, int i) {
    int mask = (1 << i);
    return (byte | mask);
}

u_int8_t reset(u_int8_t byte, int i) {
    int mask = ~(1 << i);
    return byte & mask;
}

int main() 
{
    u_int8_t byte;
    int i;

    scanf("%hhu %d", &byte, &i);
    if (!is_set(byte, i)) {
        printf("bitul %d din byteul %d NU este setat!\n", i, byte);
    } else {
        printf("bitul %d din byteul %d este setat!\n", i, byte);
    }

    byte = set(byte, i);
    printf("after set: %hhu\n", byte);

    byte = reset(byte, i);
    printf("after reset: %hhu\n", byte);

    return 0;
}
