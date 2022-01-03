#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int dmax = 20;
int n;

int sol[dmax];

void write(int p){
    for(int i = 1; i <= p; i++){
        printf("%d ", sol[i]);
    }
    printf("\n");
}

void bkt(int k, int p){
    
    if(k - 1 == p){
        write(p);
    }
    else{
        for(int i = sol[k - 1] + 1; i <= n - p + k; i++){
            sol[k] = i;
            bkt(k + 1, p);
        }
    }
}

int main(void){
    
    scanf("%d", &n);
    bkt(1, 2);
    
    return 0;
}

