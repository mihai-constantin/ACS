#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphM* createGraphAdjMatrix(int numberOfNodes){
	
    TGraphM* graph = (TGraphM*) malloc(sizeof(TGraphM*));
    
    if(!graph)
        return NULL;
    
    graph -> nn = numberOfNodes;
    
    graph -> Ma = (int**) malloc(numberOfNodes * sizeof(int*));
    
    for(int i = 0; i < numberOfNodes; i++)
        graph -> Ma[i] = (int*) malloc(numberOfNodes * sizeof(int));
    
    /* initializare matrice de adiacenta */
    for(int i = 0; i < numberOfNodes; i++)
        for(int j = 0; j < numberOfNodes; j++)
            graph -> Ma[i][j] = 0;
    
    return graph;
}

TGraphL* createGraphAdjList(int numberOfNodes){
    
    TGraphL* graph = (TGraphL*) malloc(sizeof(TGraphL));
    
    if(!graph)
        return NULL;
    
    graph -> nn = numberOfNodes;
    
    graph -> adl = (TNode**) malloc(numberOfNodes * sizeof(TNode*));
    
    for(int i = 0; i < numberOfNodes; i++)
        graph -> adl[i] = NULL;
    
    return graph;
}

void addEdgeMatrix(TGraphM* graph, int v1, int v2){
    
    graph -> Ma[v1][v2] = graph -> Ma[v2][v1] = 1;
}

void addEdgeList(TGraphL* graph, int v1, int v2){
   
    /* muchia v1 - v2 */
    TNode* node_1 = (TNode*) malloc(sizeof(TNode));
    
    node_1 -> v = v2;
    node_1 -> next = graph -> adl[v1];
    
    graph -> adl[v1] = node_1;

    /* muchia v2 - v1 */
    TNode* node_2 = (TNode*) malloc(sizeof(TNode));
    
    node_2 -> v = v1;
    node_2 -> next = graph -> adl[v2];
    
    graph -> adl[v2] = node_2;
}

void removeEdgeMatrix(TGraphM* graph, int v1, int v2){
    
    graph -> Ma[v1][v2] = graph -> Ma[v2][v1] = 0;
}

void removeNodeMatrix(TGraphM* graph, int v){
    
    for(int i = 0; i < graph -> nn; i++)
        graph -> Ma[v][i] = graph -> Ma[i][v] = 0;
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
    
    /* elimin muchia v1 - v2 */
    TNode* iterator = graph -> adl[v1];
    TNode* prev = NULL;
    
    while(iterator -> v != v2)
    {
        prev = iterator;
        iterator = iterator -> next;
    }
    
    if(!prev)
        graph -> adl[v1] = graph -> adl[v1] -> next;
    else
        prev -> next = iterator -> next;
    
    /* elimin muchia v2 - v1 */
    iterator = graph -> adl[v2];
    prev = NULL;
    
    while(iterator -> v != v1)
    {
        prev = iterator;
        iterator = iterator -> next;
    }
    
    if(!prev)
        graph -> adl[v2] = graph -> adl[v2] -> next;
    else
        prev -> next = iterator -> next;
}

void removeNodeList(TGraphL* graph, int v){
    
    TNode* iterator = graph -> adl[v];

    while(iterator)
    {
        removeEdgeList(graph, iterator -> v, v);
        iterator = iterator -> next;
    }
}

void destroyGraphAdjMatrix(TGraphM *graph){
    
    for(int i = 0; i < graph -> nn; i++)
        free(graph -> Ma[i]);
    
    free(graph -> Ma);
    free(graph);
}

void destroyGraphAdjList(TGraphL* graph){
    
    for(int i = 0; i < graph -> nn; i++)
        free(graph -> adl[i]);
    
    free(graph -> adl);
    free(graph);
}

List* dfsIterativeGM(TGraphM* graph, int s){
    
    int* visited = (int*) malloc(graph -> nn * sizeof(int));
    
    /* initializare vector visited */
    for(int i = 0; i < graph -> nn; i++)
        visited[i] = 0;
    
    List* list = createList();
    Stack* stack = createStack();
    
    /* adaug in stiva nodul de start */
    enqueue(stack, s);
    visited[s] = 1;
    
    while(!isStackEmpty(stack))
    {
        s = top(stack);
        pop(stack);
        
        enqueue(list, s);
        
        /* parcurg vecinii nodului s */
        for(int i = 0; i < graph -> nn; i++)
            if(graph -> Ma[s][i] == 1 && !visited[i])
            {
                enqueue(stack, i);
                visited[i] = 1;
            }
    }
    
	return list;
}

void dfsRecGMHelper(TGraphM* G,int* visited, List* path, int s){
    
    visited[s] = 1;
    enqueue(path, s);
    
    /* parcurg vecinii nodului s */
    for(int i = 0; i < G -> nn; i++)
        if(G -> Ma[s][i] && !visited[i]) /* exista muchie de la nodul s la nodul i */
            dfsRecGMHelper(G, visited, path, i);
}

List* dfsRecursiveGM(TGraphM* G, int s){
    
    List* list = createList();
    
    int* visited = (int*) malloc(G -> nn * sizeof(int));
    
    /* initializare vector visited */
    for(int i = 0; i < G -> nn; i++)
        visited[i] = 0;
    
    dfsRecGMHelper(G, visited, list, s);
    
	return list;
}

void dfsRecGLHelper(TGraphL* G, int* visited, List* path, int s){
    
    visited[s] = 1;
    enqueue(path, s);
    
    /* parcurg vecinii nodului s */
    TNode* iterator = G -> adl[s];
    
    while(iterator)
    {
        if(!visited[iterator -> v])
            dfsRecGLHelper(G, visited, path, iterator -> v);
        
        iterator = iterator -> next;
    }
}

List* dfsRecursiveGL(TGraphL* G, int s){
	
    List* list = createList();
    
    int* visited = (int*) malloc(G -> nn * sizeof(int));
    
    /* initializare vector visited */
    for(int i = 0; i < G -> nn; i++)
        visited[i] = 0;
    
    dfsRecGLHelper(G, visited, list, s);
    
    return list;
}

List* bfsGL(TGraphL* graph, int s){
    
    List* list = createList();
    Queue* queue = createQueue();
    
    int* visited = (int*) malloc(graph -> nn * sizeof(int));
    
    /* initializare vector visited */
    for(int i = 0; i < graph -> nn; i++)
        visited[i] = 0;
    
    // introduc in coada nodul de start
    enqueue(queue, s);
    visited[s] = 1;
    
    enqueue(list, s); // introduc in lista nodul de start
    
    while(!isQueueEmpty(queue))
    {
        int x = front(queue);
        
        // parcurg vecinii y ai lui x
        TNode* iterator = graph -> adl[x];
        
        while(iterator)
        {
            if(!visited[iterator -> v])
            {
                enqueue(queue, iterator -> v);
                enqueue(list, iterator -> v);
                visited[iterator -> v] = 1;
            }
    
            iterator = iterator -> next;
        }
    
        dequeue(queue);
    }
    
	return list;
}
