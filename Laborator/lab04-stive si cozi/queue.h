#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct cel
{
    Item elem;
    struct cel* next;
}QueueCel, *TQueue;

typedef struct {TQueue front, rear;} AQ;


AQ* InitQueue()
{
   AQ* queue = (AQ*) malloc(sizeof(AQ));

   queue -> front = NULL;
   queue -> rear = NULL;

   return queue;
}

int IsEmptyQueue(AQ *q)
{
   if(!q)
   		return 1;

   	if(!q -> front)
   		return 1;

   	return 0;
}


void Enqueue(AQ *q, Item el)
{
	TQueue node = (TQueue) malloc(sizeof(QueueCel));

	if(!node)
		return;

	node -> elem = el;
	node -> next = NULL;

    if(q -> front == NULL)
    {
    	q -> front = node;
    	q -> rear = node;
    }
    else
    {
    	q -> rear -> next = node;
    	q -> rear = node;
    }
}


Item Dequeue(AQ *q)
{
	if(q)
	{
	   TQueue node = q -> front;

  		q -> front = q -> front -> next;

    	return node -> elem;
	}
}

Item Front(AQ *q)
{
    if(q)
    	return q -> front -> elem;

}

void PrintQueue(AQ *q)
{
	if(!q)
		return;

	TQueue iterator = q -> front;

	while(iterator)
	{
		printf("%d ", iterator -> elem);
		iterator = iterator -> next;
	}
}
#endif
