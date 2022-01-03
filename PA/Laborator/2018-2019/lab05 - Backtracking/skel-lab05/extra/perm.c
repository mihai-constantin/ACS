#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int dmax = 10;
int n;

int sol[dmax];
bool c[dmax];

void write(){
    for(int i = 1; i <= n; i++){
        printf("%d ", sol[i]);
    }
    printf("\n");
}

void bkt(int p){
    if(p - 1 == n) {
        write();
        return;
    }
    for(int i = 1; i <= n; i++){
        if(!c[i]){
            sol[p] = i;
            c[i] = true;
            bkt(p + 1);
            c[i] = false;
        }
    }
}

int main(void){
    
    scanf("%d", &n);
    bkt(1);
    
    return 0;
}
