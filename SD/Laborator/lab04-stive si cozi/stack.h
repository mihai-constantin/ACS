#ifndef STACK_H_D
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct cel
{
    Item elem;
    struct cel* next;
}StackCel, *TStack;


TStack InitStack()
{
	TStack stack = (TStack) malloc(sizeof(StackCel));

	stack = NULL;

	return stack;
}

int IsEmptyStack (TStack s)
{
    if(!s)
    	return 1;

    return 0;
}

TStack Push(TStack s, Item el)
{
    TStack node = (TStack) malloc(sizeof(StackCel));

    if(!node)
    	return NULL;

    node -> elem = el;
    node -> next = NULL;

    if(!s)
    {
    	s = node;
    }
    else
    {
    	node -> next = s;
    	s = node;
    }

    return s;
}


TStack Pop(TStack s,Item *el)
{
    if(!s)
    	return NULL;

    TStack aux = s;

    s = s -> next;

    free(aux);

    return s;
}

Item Top (TStack s)
{
	if(s)
		return s -> elem;
}

void PrintStack(TStack s)
{
   if(!s)
   	return;

   while(s)
   {
   		printf("%d ", s -> elem);
   		s = s -> next;
   }
}

void PrintStack2(TStack s)
{
   if(!s)
    return;

   while(s)
   {
      printf("%c", s -> elem);
      s = s -> next;
   }
}



#endif // LINKEDSTACK_H_INCLUDED
