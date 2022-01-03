#include <stdio.h>

#define N 100

void sum_right_neighbour(int v[N], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        v[i] = v[i] + v[i + 1];
    }
}

void sum_left_neighbour(int v[N], int n) {
    int i;
    for (i = n - 1; i >= 1; i--) {
        v[i] = v[i] + v[i - 1];
    }
}

void create_array(int v[N], int arr[N], int n) {
    int i;
    long long p = 1;
    for (i = 0; i < n; i++) {
        p = p * v[i];
    }
    for (i = 0; i < n; i++) {
        arr[i] = p/v[i];
    }
}

void remove_min(int v[N], int n) {
    // initializare minim
    int minim = v[0];
    int pos = 0;
    int i;
    for (i = 1; i < n; i++) {
        if (minim > v[i]) {
            minim = v[i];
            pos = i;
        }
    }
    // printf("%d %d\n", minim, pos);
    for (i = pos; i < n - 1; i++) {
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
    /**
     *  v: 1 2 3 4 5
     *  min = 1; pos = 0
     *  i = 0:4
     *  i = 0 -> v[0] = v[1] -> v: 2 2 3 4 5
     *  i = 1 -> v[1] = v[2] -> v: 2 3 3 4 5
     *  i = 2 -> v[2] = v[3] -> v: 2 3 4 4 5
     *  i = 3 -> v[3] = v[4] -> v: 2 3 4 5 5
     * 
     */
    for (i = pos; i < n - 1; i++) {
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
    // print_vector(v, n); // 3 5 7 9 5
    
    //sum_left_neighbour(v, n);
    //print_vector(v, n); // 1 3 5 7 9
    
    // create_array(v, arr, n);

    // arr[0] = p / v[0]
    // arr[1] = (1 * 2 * 3 * 4 * 5) / v[1]
    // arr[2] = (1 * 2 * 3 * 4 * 5) / v[2]
    // arr[3] = (1 * 2 * 3 * 4 * 5) / v[3]
    // arr[4] = (1 * 2 * 3 * 4 * 5) / v[4]

    // print_vector(arr, n);

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
