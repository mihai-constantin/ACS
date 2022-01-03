/**
 * Exercitiul 1
 * Determinare sistem big/little endian
 * Detalii: https://en.wikipedia.org/wiki/Endianness
 */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    u_int32_t x = 0xFAFBFCFD; // 4 bytes
    u_int8_t x1, x2, x3, x4; // 1 byte
    x1 = *((u_int8_t*)&x);
    x2 = *((u_int8_t*)&x + 1);
    x3 = *((u_int8_t*)&x + 2);
    x4 = *((u_int8_t*)&x + 3);

    /**
     *  u_int32_t x;
     *  &x : u_int32_t*
     * 
     *  (u_int8_t*) &x : u_int8_t*
     *  (u_int8_t*) &x+1 : u_int8_t*
     *  *((u_int8_t*) &x+1) : u_int8_t
     * 
     */

    // FA FB FC FD - big endian
    // FD FC FB FA - little endian
    printf("%X %X %X %X\n", x1, x2, x3, x4);

    return 0;
}
