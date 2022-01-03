#include <stdio.h>
#include <stdlib.h>
#define MAX_DIM 100
typedef int Item;
#include "queue.h"
#include <math.h>

void ReadArray(int a[MAX_DIM], int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("a[%d]=", i);
        scanf("%d", &a[i]);
    }

}

void PrintArray(int a[MAX_DIM], int n)
{
    int i;
    for(i=0;i<n;i++)
      printf("%d ", a[i]);
    printf("\n");
}


void RadixSort(int a[MAX_DIM], int n)
{
    AQ** queue = (AQ**) malloc(10 * sizeof(AQ*));

    int b[MAX_DIM], aux[MAX_DIM], ok, i;

    for(i = 0; i < n; i++)
    {
        aux[i] = a[i];
        b[i] = a[i];
    }

    int count = 0;

    do{
       
        ok = 1;
        count++;

        for(i = 0; i < 10; i++)
            queue[i] = InitQueue();

        for(i = 0; i < n; i++)
        {
            Enqueue(queue[b[i] % 10], aux[i]);
            b[i] /= 10; 
        }

        int k = -1;

        for(i = 0; i < 10; i++)
        {
            // fac Dequeue pe fiecare coada
            TQueue iterator = queue[i] -> front;

            while(iterator)
            {
                aux[++k] = iterator -> elem;
                iterator = iterator -> next;
            }
        }

        for(i = 0; i < n - 1; i++)
            if(aux[i + 1] < aux[i])
                ok = 0;

        for(i = 0; i < n; i++)
            b[i] = aux[i] / pow(10, count);

    }while(!ok);

    for(i = 0; i < n; i++)
        a[i] = aux[i];
}

int main()
{
    int a[MAX_DIM], n;
    printf("n="); scanf("%d", &n);
    ReadArray(a, n);
    RadixSort(a,n);
    PrintArray(a, n);

    return 0;
}
