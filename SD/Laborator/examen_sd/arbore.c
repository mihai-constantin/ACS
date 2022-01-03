#include <stdio.h>
#include <stdlib.h>

#define inf 100002

typedef struct TNode{
    int v;
    struct TNode* next;
}TNode;

typedef struct TGraph{
    int nn;
    int* info; /* valoarea din fiecare nod */
    TNode** adl;
}TGraph;

int answer = inf;

TGraph* createGraph(int numberofNodes){
    
    TGraph* graph = (TGraph*) malloc(sizeof(TGraph));
    
    graph -> nn = numberofNodes;
    
    graph -> info = (int*) calloc(1 + numberofNodes, sizeof(int));
    
    graph -> adl = (TNode**) malloc((1 + numberofNodes) * sizeof(TNode*));
    
    for(int i = 0; i <= numberofNodes; i++)
        graph -> adl[i] = NULL;
    
    return graph;
}

void addEdge(TGraph* graph, int x, int y){
    
    /* aloc memorie pentru un nod */
    
    TNode* node = (TNode*) malloc(sizeof(TNode));
    
    node -> v = y;
    node -> next = NULL;
    
    if(!graph -> adl[x])
        graph -> adl[x] = node;
    else{
        node -> next = graph -> adl[x];
        graph -> adl[x] = node;
    }
}

void printGraph(TGraph* graph){
    
    for(int i = 1; i <= graph -> nn; i++){
        
        printf("[%d]: ", i);
        
        TNode* iterator = graph -> adl[i];
        
        while(iterator)
        {
            printf("%d ", iterator -> v);
            iterator = iterator -> next;
        }
        
        printf("\n");
    }
}

void dfs(TGraph* graph, int* visited, int K, int node){
    
    visited[node] = 1;
    
    if(graph -> info[node] > K && graph -> info[node] < answer)
        answer = graph -> info[node];
    
    /* parcurg vecinii nodului node */
    TNode* iterator = graph -> adl[node];
    
    while(iterator){
        if(!visited[iterator -> v])
            dfs(graph, visited, K, iterator -> v);
        
        iterator = iterator -> next;
    }
}

int main()
{
    int N;
    
    scanf("%d", &N);
    TGraph* graph = createGraph(N);
    
    for(int i = 1; i <= N; i++)
        scanf("%d", &graph -> info[i]);
    
    for(int i = 1; i < N; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        
        addEdge(graph, x, y);
        addEdge(graph, y, x);
    }
    
    printGraph(graph);
    
    int* visited = (int*) calloc(1 + graph -> nn, sizeof(int));
    
    int K;
    scanf("%d", &K);
    
    dfs(graph, visited, K, 1);
    
    printf("answer = %d\n", answer);
    
    return 0;
}
