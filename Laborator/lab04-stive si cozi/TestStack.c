#include <stdio.h>
#include <stdlib.h>
typedef int Item;
#include "stack.h"


int main()
{

    TStack st;
    Item el;
    st=InitStack();

    st=Push(st, 1); st=Push(st, 2); st=Push(st, 3);
    st=Push(st, 4); st=Push(st, 5); st=Push(st, 6);

    printf("\n--- Stack should be: 6 5 4 3 2 1 \n");
    PrintStack(st);

    st=Pop(st, &el); st=Pop(st, &el); st=Pop(st, &el);
    printf("\n--- Stack should be: 3 2 1 \n");
    PrintStack(st);

    printf("\n--- Top should be 3 \n");
    printf("Top = %d ", Top(st));
	printf("\n");

    return 0;

}
