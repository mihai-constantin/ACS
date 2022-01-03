#include <stdio.h>
#include <stdlib.h>
#include "Util.c"

#define inf 100002

typedef struct node{
    int v;
    int cost;
    struct node* next;
}TNode;

typedef struct TGraphL{
    int nn;
    TNode** adl;
}TGraphL;

TGraphL* createGraph(int numberofNodes){
    
    TGraphL* graph = (TGraphL*) malloc(sizeof(TGraphL));
    
    graph -> nn = numberofNodes;
    
    graph -> adl = (TNode**) malloc((numberofNodes + 1) * sizeof(TNode*));
    
    for(int i = 0; i <= numberofNodes; i++)
        graph -> adl[i] = NULL;
    
    return graph;
}

void addEdge(TGraphL* graph, int x, int y, int c){
    
    /* aloc memorie pentru un nod */
    TNode* node = (TNode*) malloc(sizeof(TNode));
    
    node -> v = y;
    node -> cost = c;
    node -> next = NULL;
    
    if(!graph -> adl[x])
        graph -> adl[x] = node;
    else
    {
        node -> next = graph -> adl[x];
        graph -> adl[x] = node;
    }
}

void printGraph(TGraphL* graph){
    
    printf("=== Reprezentare graf ===\n");
    
    for(int i = 1; i <= graph -> nn; i++){
        
        printf("[%d]: ", i);
        
        TNode* iterator = graph -> adl[i];
        
        while(iterator){
            printf("%d ", iterator -> v);
            iterator = iterator -> next;
        }
        
        printf("\n");
    }
}

void dijkstra(TGraphL* graph, int node, int cost){
    
    /* Dijkstra cu coada. Doamne, cat de frumos :) */
    
    int* distance = (int*) malloc((graph -> nn + 1) * sizeof(int));
    
    for(int i = 0; i <= graph -> nn; i++)
        distance[i] = inf;
    
    Queue* queue = createQueue();
    
    /* introduc in coada nodul de start */
    enqueue(queue, node);
    distance[node] = 0;
    
    while(!isQueueEmpty(queue)){
        
        int x = front(queue);
        
        /* parcurg vecinii nodului x */
        TNode* iterator = graph -> adl[x];
        
        while(iterator){
            
            if(distance[iterator -> v] > distance[x] + iterator -> cost){
                distance[iterator -> v] = distance[x] + iterator -> cost;
                enqueue(queue, iterator -> v);
            }
            
            iterator = iterator -> next;
        }
        
        dequeue(queue);
    }
    
    printf("=== Dijkstra ===\n");
    
    for(int i = 1; i <= graph -> nn; i++)
        printf("%d ", distance[i]);
    
    printf("\n");
    
    printf("=== Noduri accesibile din %d ===\n", node);
    
    /* nodurile accesibile din node cu distanta cel mult cost */
    for(int i = 1; i <= graph -> nn; i++)
        if(distance[i] <= cost)
            printf("%d ", i);
    
    printf("\n");
}

void prim(TGraphL* graph){
    
    /* Prim cu coada. Doamne, cat de frumos :) */
    
    int node = 1;
    
    int* distance = (int*) malloc((graph -> nn + 1) * sizeof(int));
    
    for(int i = 0; i <= graph -> nn; i++)
        distance[i] = inf;
    
    int* visited = (int*) calloc(1 + graph -> nn, sizeof(int));
    int* parent = (int*) calloc(1 + graph -> nn, sizeof(int));
    
    Queue* queue = createQueue();
    
    /* introduc in coada nodul de start */
    enqueue(queue, node);
    distance[node] = 0;
    
    while(!isQueueEmpty(queue)){
        
        int x = front(queue);
        
        visited[x] = 1;
        
        /* parcurg vecinii nodului x */
        TNode* iterator = graph -> adl[x];
        
        while(iterator){
            
            if(distance[iterator -> v] > iterator -> cost && !visited[iterator -> v]){
                parent[iterator -> v] = x;
                distance[iterator -> v] = iterator -> cost;
                enqueue(queue, iterator -> v);
            }
            
            iterator = iterator -> next;
        }
        
        dequeue(queue);
    }
    
    printf("=== Prim ===\n");
    
    for(int i = 1; i <= graph -> nn; i++)
        printf("%d %d\n", i, parent[i]);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    
    TGraphL* graph = createGraph(N);
    
    for(int i = 0; i < M; i++){
        int x, y, c;
        scanf("%d %d %d", &x, &y, &c);
        
        /* graf neorientat */
        addEdge(graph, x, y, c);
        addEdge(graph, y, x, c);
    }
    
    printGraph(graph);
    
    int node, cost;
    scanf("%d %d", &node, &cost);
    
    dijkstra(graph, node, cost);
    
    prim(graph);
    
    return 0;
}
