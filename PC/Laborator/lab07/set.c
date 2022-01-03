/**
 * Bitset
 */
#include <stdio.h>
#include <math.h>

#define SET_SIZE 100 
typedef unsigned char SET[SET_SIZE];

#define max(a, b) (a > b ? a : b)

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

void print_bits(int n) {
    if (!n) {
        printf("00000000\n");
        return;
    }
    int x = log2(n) + 1;
    for (int i = max(7, x - 1); i >= 0; i--) {
        if (!(n & (1 << i))) {
            printf("0");
        } else {
            printf("1");
        }
    }
    printf("\n");
}

void delete_all_from_set(SET s) {
    for (int i = 0; i < SET_SIZE; i++) {
        s[i] = 0;
    }
}

void insert_in_set(SET s, unsigned int n) {
    u_int8_t byte = n / 8;
    int i = n % 8;
    // printf("byte: %hhu\n", byte);
    // printf("i: %d\n", i);
    s[byte] = set(s[byte], i);
}

void delete_from_set(SET s, unsigned int n) {
    u_int8_t byte = n / 8;
    int i = n % 8;
    s[byte] = reset(s[byte], i);
}

int is_in_set(SET s, unsigned int n) {
    u_int8_t byte = n / 8;
    int i = n % 8;
    return is_set(s[byte], i);
}

int count_ones(int n) {
    if (!n) {
        return 0;
    }
    int x = log2(n) + 1;
    int nr = 0;
    for (int i = x - 1; i >= 0; i--) {
        if ((n & (1 << i))) {
            nr++;
        }
    }
    return nr;
}

int card_set(SET s) {
    int nr = 0;
    for (int i = 0; i < SET_SIZE; i++) {
        nr += count_ones(s[i]);
    }
    return nr;
}

int is_empty_set(SET s) {
    if (!card_set(s)) {
        return 1;
    }
    return 0;
}

void helper_print_set(SET s, int n, int idx) {
    if (!n) {
        return;
    }
    int x = log2(n) + 1;
    for (int i = max(7, x - 1); i >= 0; i--) {
        if ((n & (1 << i))) {
            printf("%d ", 8 * idx + i);
        }
    }
}

void print_set(SET s) {
    // for (int i = 0; i < SET_SIZE; i++) {
    //     printf("%d: ", i);
    //     print_bits(s[i]);
    // }
    printf("S: ");
    for (int i = 0; i < SET_SIZE; i++) {
        helper_print_set(s, s[i], i);
    }
    printf("\n");
}

void read_set(SET s) {
    printf("Enter n: ");
    int n ,x;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        insert_in_set(s, x);
    }
}

void merge_set(SET a, SET b, SET c) {
    for (int i = 0; i < SET_SIZE; i++) {
        c[i] = a[i] | b[i];
    }
}

void intersect_set(SET a, SET b, SET c) {
    for (int i = 0; i < SET_SIZE; i++) {
        c[i] = a[i] & b[i];
    }
}

void helper_diff_set(SET a, SET b, SET c, int n, int idx) {
    if (!n) {
        return;
    }
    int x = log2(n) + 1;
    for (int i = max(7, x - 1); i >= 0; i--) {
        if ((n & (1 << i))) {
            if (!is_in_set(b, 8 * idx + i)) {
                insert_in_set(c, 8 * idx + i);
            }
        }
    }
}

void diff_set(SET a, SET b, SET c) {
    for (int i = 0; i < SET_SIZE; i++) {
        helper_diff_set(a, b, c, a[i], i);
    }
}

int main() 
{
    // SET s;
    // delete_all_from_set(s);
    // insert_in_set(s, 13);
    // insert_in_set(s, 8);
    // print_set(s);
    // printf("is_in_set: %d\n", is_in_set(s, 8));
    // printf("card_set: %d\n", card_set(s));
    // delete_from_set(s, 8);
    // print_set(s);
    // printf("is_in_set: %d\n", is_in_set(s, 8));
    // printf("card_set: %d\n", card_set(s));
    // insert_in_set(s, 8);
    // printf("card_set: %d\n", card_set(s));
    // printf("is_empty_set: %d\n", is_empty_set(s));
    // delete_all_from_set(s);
    // printf("is_empty_set: %d\n", is_empty_set(s));
    // print_set(s);
    // read_set(s);
    // print_set(s);
    // delete_all_from_set(s);

    SET a, b, c;
    delete_all_from_set(a);
    delete_all_from_set(b);
    delete_all_from_set(c);
    read_set(a);
    read_set(b);
    // merge_set(a, b, c);
    // intersect_set(a, b, c);
    diff_set(a, b, c);
    print_set(a);
    print_set(b);
    print_set(c);

    return 0;
}
