#include <stdio.h>

#define N 100

void sum_right_neighbour(int v[N], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        v[i] += v[i + 1];
    }
}

void sum_left_neighbour(int v[N], int n) {
    int i;
    for (i = n - 1; i > 0; i--) {
        v[i] += v[i - 1];
    }
}

void create_array(int v[N], int arr[N], int n) {
    int i;
    long long p = 1;
    for (i = 0; i < n; i++) {
        p *= v[i];
    }
    for (i = 0; i < n; i++) {
        arr[i] = p/v[i];
    }
}

void remove_min(int v[N], int n) {
    int minim = v[0];
    int pos = 0;
    int i;
    for (i = 1; i < n; i++) {
        if (minim > v[i]) {
            minim = v[i];
            pos = i;
        }
    }
    for (i = pos; i < n; i++) {
        v[i] = v[i + 1];
    }
}

void remove_max(int v[N], int n) {
    int maxim = v[0];
    int pos = 0;
    int i;
    for (i = 1; i < n; i++) {
        if (maxim < v[i]) {
            maxim = v[i];
            pos = i;
        }
    }
    for (i = pos; i < n; i++) {
        v[i] = v[i + 1];
    }
}

void print_vector(int v[N], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    int v[N] = {1, 2, 3, 4, 5};
    int arr[N];
    int n = 5;
    print_vector(v, n);

    // sum_right_neighbour(v, n);
    // print_vector(v, n);
    
    // sum_left_neighbour(v, n);
    // print_vector(v, n);
    
    create_array(v, arr, n);
    print_vector(arr, n);

    char c;
    while(scanf("%c", &c)) {
        getchar(); // ignore newline
        if (c == 'q') {
            return 0;
        } else if (c == 'p') {
            print_vector(v, n);
        } else if (c == 'm') {
            remove_min(v, n);
            n--;
        } else if (c == 'M') {
            remove_max(v, n);
            n--;
        } else {
            printf("c: %c", c);
            printf("Invalid command!\n");
        }
    }

    return 0;
}
