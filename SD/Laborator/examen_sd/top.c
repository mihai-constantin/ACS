/* Sortare topologica */

#include <stdio.h>
#include <stdlib.h>

#define dim 100005
int sol[dim];
int k;

typedef struct GraphNode{
    
    int v;
    struct GraphNode* next;
    
}GraphNode;

typedef struct Graph{
    
    int nn; /* numberofNodes */
    GraphNode** adl; /* listele de adiacenta */
    
}Graph;

Graph* createGraph(int numberofNodes){
    
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    
    graph -> nn = numberofNodes;
    
    /* aloc memorie pentru listele de adiacenta */
    graph -> adl = (GraphNode**) malloc((numberofNodes + 1) * sizeof(GraphNode*));
    
    for(int i = 0; i <= numberofNodes; i++)
        graph -> adl[i] = NULL;
    
    return graph;
}

void addEdge(Graph* graph, int x, int y){
    
    /* aloc memorie pentru un nod */
    GraphNode* node = (GraphNode*) malloc(sizeof(GraphNode));
    
    node -> v = y;
    node -> next = NULL;
    
    if(!graph -> adl[x])
        graph -> adl[x] = node;
    else{
        node -> next = graph -> adl[x];
        graph -> adl[x] = node;
    }
}

void printGraph(Graph* graph){
    
    for(int i = 1; i <= graph -> nn; i++){
        
        GraphNode* iterator = graph -> adl[i];
        
        printf("[%d]: ", i);
        
        while(iterator)
        {
            printf("%d ", iterator -> v);
            iterator = iterator -> next;
        }
        
        printf("\n");
    }
}

void dfsHelper(Graph* graph, int* visited, int node){
    
    visited[node] = 1;
    
    /* parcurg vecinii nodului node */
    GraphNode* iterator = graph -> adl[node];
    
    while(iterator){
        if(!visited[iterator -> v])
            dfsHelper(graph, visited, iterator -> v);
        
        iterator = iterator -> next;
    }
    
    sol[++k] = node;
}

void dfs(Graph* graph, int* visited, int node){
    
    dfsHelper(graph, visited, node);
    
    printf("=== Sortare topologica === \n");
    
    for(int i = k; i >= 1; i--)
        printf("%d ", sol[i]);
    
    printf("\n");
}

int main()
{
    int N, M;
    
    scanf("%d %d", &N, &M);
    
    Graph* graph = createGraph(N);
    
    for(int i = 0; i < M; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        addEdge(graph, x, y);
    }
    
    printGraph(graph);
    
    /* aloc memorie pentru vectorul visited */
    
    int* visited = (int*) calloc((graph -> nn + 1), sizeof(int));
    
    for(int i = 1; i <= N; i++)
        if(!visited[i])
            dfs(graph, visited, i);
    
    return 0;
}
