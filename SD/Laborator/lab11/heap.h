#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode
{
    int  v;
    int d;
} MinHeapNode;


typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;

MinHeapNode* newNode(int v, int d)
{
    MinHeapNode* node = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    
    node -> v = v;
    node -> d = d;
    
    return node;
}

MinHeap* newQueue(int capacity)
{
    MinHeap* h = (MinHeap*) malloc(sizeof(MinHeap));
    
    h -> size = 0;
    h -> capacity = capacity;
    
    h -> pos = (int*) malloc(capacity * sizeof(int));
    h -> elem = (MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));
    
    return h;
}

int getParent(int i) {
    return floor((i - 1) / 2);
}

void swap(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* aux = *a;
    
    *a = *b;
    *b = aux;
}

void SiftUp(MinHeap* h, int v, int d)
{
    if(h -> size == h -> capacity)
    {
        h -> capacity *= 2;
        h -> elem = (MinHeapNode**) realloc(h -> elem, h -> capacity * sizeof(MinHeapNode*));
    }
    
    MinHeapNode* node = newNode(v, d);
    
    h -> elem[h -> size] = node;
    h -> size++;
    
    h -> pos[v] = h -> size - 1;
    
    int idx = h -> pos[v];
    
    int parent = getParent(idx);
    
    while (parent >= 0 && h->elem[parent] -> d > h->elem[idx] -> d)
    {
        // update positions
        h -> pos[h -> elem[parent] -> v] = idx;
        h -> pos[h -> elem[idx] -> v] = parent;
        swap(&(h -> elem[parent]), &(h -> elem[idx]));
        
        idx = parent;
        parent = getParent(idx);
    }
}

int getLeftChild(int i) {
    return 2 * i + 1;
}

int getRightChild(int i) {
    return 2 * i + 2;
}

void SiftDown(MinHeap* h, int idx)
{
    int leftChild = getLeftChild(idx);
    int rightChild = getRightChild(idx);
    int smallest = idx;
    
    if (leftChild < h->size && h -> elem[leftChild] -> d < h -> elem[smallest] -> d) {
        smallest = leftChild;
    }
    
    if (rightChild < h->size && h -> elem[rightChild] -> d < h -> elem[smallest] -> d) {
        smallest = rightChild;
    }
    
    if (smallest != idx)
    {
        // swap positions
        h -> pos[h -> elem[smallest] -> v] = idx;
        h -> pos[h -> elem[idx] -> v] = smallest;
        
        // swap nodes
        swap(&(h -> elem[smallest]), &(h -> elem[idx]));
        
        /* Carry on. */
        SiftDown(h, smallest);
    }
}

int isEmpty(MinHeap* h)
{
    return h -> size == 0;
}

MinHeapNode* getMin(MinHeap* h)
{
    return h -> elem[0];
}

MinHeapNode* removeMin(MinHeap* h)
{
    MinHeapNode* min = getMin(h);
    MinHeapNode* last = h -> elem[h -> size - 1];
    
    h -> elem[0] = last;
    
    // update positions
    h -> pos[min -> v] = h -> size - 1; // ?
    h -> pos[last -> v] = 0;
    
    h -> size--;
    SiftDown(h, 0);
    
    return min;
}

int isInMinHeap(MinHeap *h, int v)
{
    for(int i = 0; i < h -> size; i++)
        if(h -> elem[i] -> v == v)
            return 1;
    
    return 0;
}

#endif

