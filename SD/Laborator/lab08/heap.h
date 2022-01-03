#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */

typedef struct {
    Item content;
    int prior; /* You will compare elements based on this. */
} ItemType;

typedef struct heap {
    long int capacity;
    long int size;
    ItemType *elem;
} PriQueue, *APriQueue;


APriQueue makeQueue(int capacity) {
	APriQueue queue = malloc(sizeof(PriQueue));
	if (queue == NULL) {
		return NULL;
	}
	queue->elem = malloc(capacity * sizeof(ItemType));
	if (queue->elem == NULL) {
		free(queue);
		return NULL;
	}
	queue->capacity = capacity;
	queue->size = 0;
	return queue;
}

int getLeftChild(int i) {
	return 2 * i + 1;
}

int getRightChild(int i) {
	return 2 * i + 2;
}

int getParent(int i) {
	return (i - 1)/2;
}

ItemType getMax(APriQueue h) {
	return h->elem[0];
}

void siftUp(APriQueue h, int idx) {
	int p = getParent(idx);
	ItemType aux;
	if(h->elem[idx].prior > h->elem[p].prior) {
		//le interschimb
		aux = h->elem[idx];
		h->elem[idx] = h->elem[p];
		h->elem[p] = aux;
		siftUp(h, p);
	}
    
	return;
}

void insert(APriQueue h, ItemType x) {
	if (h->size == h->capacity) {
		//nu am loc de elemente noi
		h = realloc(h, 2 * h->capacity);
		h->capacity = 2 * h->capacity;
	}
	//adaug noul element
	long int size = h->size;	
	h->elem[size] = x;

	// il mut mai sus la pozitia lui corecta
	siftUp(h, size);
	h->size = size + 1;
}

void siftDown(APriQueue h, int idx) {
	ItemType aux;
	int left = getLeftChild(idx);
	int right = getRightChild(idx);
	if (left >= h->size) {
		//nu are copil stanga, nu are nici dreapta
		return;
	}

	int max = left;
	if (right < h->size && h->elem[right].prior > h->elem[max].prior) {
		max = right;
	}
	if (h->elem[max].prior > h->elem[idx].prior) {
		//le interschimb
		aux = h->elem[max];
		h->elem[max] = h->elem[idx];
		h->elem[idx] = aux;
		siftDown(h, max);
	} 
}

ItemType removeMax(APriQueue h) {
	// interschimb primul cu ultimul
	long int size = h->size;
	ItemType aux = h->elem[0];
	h->elem[0] = h->elem[size - 1];
	h->elem[size - 1] = aux;
	
	// ma sigur ca arborele devine heap
	h->size = size - 1;
	siftDown(h, 0);
	return aux;
}

#endif

