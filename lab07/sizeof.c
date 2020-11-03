/**
 * Exemplu utilizare sizeof
 */
#include <stdio.h>
 
int main() {
    // afiseaza dimensiunea tipurilor si a unor variabile de un anumit tip
    char xc;
    printf("sizeof(unsigned char) = %ld B\n", sizeof(unsigned char));
    printf("sizeof(char) = %ld B\n", sizeof(char));
    printf("sizeof(xc) = %ld B\n", sizeof(xc));
 
    short int xs;
    printf("sizeof(unsigned short int) = %ld B\n", sizeof(unsigned short int));
    printf("sizeof(short int) = %ld B\n", sizeof(short int));
    printf("sizeof(xs) = %ld B\n", sizeof(xs));
 
    int xi;
    printf("sizeof(unsigned int) = %ld B\n", sizeof(unsigned int));
    printf("sizeof(int) = %ld B\n", sizeof(int));
    printf("sizeof(xi) = %ld B\n", sizeof(xi));
 
    // afiseaza dimensiunea unor tablouri cu dimensiune cunoscuta
    char vc[100];
    short int vs[100];
    int vi[100];
    printf("sizeof(vc) = %ld B\n", sizeof(vc));
    printf("sizeof(vs) = %ld B\n", sizeof(vs));
    printf("sizeof(vi) = %ld B\n", sizeof(vi));
 
    return 0;
}
