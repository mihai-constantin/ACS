#include <stdio.h>
#include <stdlib.h>
typedef int Item;
#include "queue.h"



int main()
{
    AQ *q;

    q=InitQueue();

    Enqueue(q,1); Enqueue(q,2); Enqueue(q,3);
    Enqueue(q,4); Enqueue(q,5); Enqueue(q,6);

    printf("\n --- Queue should be: 1 2 3 4 5 6 \n");
    PrintQueue(q);

    Dequeue(q); Dequeue(q); Dequeue(q);
    printf("\n --- Queue should be: 4 5 6 \n");
    PrintQueue(q);

    printf("\n --- Front should be 4 \n");
    printf("Front = %d ", Front(q));
	printf("\n");


    return 0;
}
