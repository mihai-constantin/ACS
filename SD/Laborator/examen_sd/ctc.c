#include <stdio.h>
#include <stdlib.h>

#define dmax 100005

typedef struct TNode{
    int v;
    struct TNode* next;
}TNode;

typedef struct TGraphL{
    int nn;
    TNode** adl;
}TGraphL;

int sol[dmax];
int k;

TGraphL* createGraph(int numberofNodes){
    
    TGraphL* graph = (TGraphL*) malloc(sizeof(TGraphL));
    
    graph -> nn = numberofNodes;
    
    graph -> adl = (TNode**) malloc((1 + numberofNodes) * sizeof(TNode*));
    for(int i = 0; i <= numberofNodes; i++)
        graph -> adl[i] = NULL;
    
    return graph;
}

void addEdge(TGraphL* graph, int x, int y){
    
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

void printGraph(TGraphL* graph){

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

void dfs(TGraphL* graph, int* visited, int node){
    
    visited[node] = 1;
    
    /* parcurg vecinii nodului node */
    TNode* iterator = graph -> adl[node];
    
    while(iterator){
        if(!visited[iterator -> v])
            dfs(graph, visited, iterator -> v);
        iterator = iterator -> next;
    }
    
    sol[++k] = node;
}

void dfs2(TGraphL* graph, int* visited, int node){
    
    visited[node] = 1;
    
    /* parcurg vecinii nodului node */
    TNode* iterator = graph -> adl[node];
    
    while(iterator){
        if(!visited[iterator -> v])
            dfs2(graph, visited, iterator -> v);
        iterator = iterator -> next;
    }
}

int main()
{
    FILE* in = fopen("graph.in", "r");
    
    int N, M;
    fscanf(in, "%d %d", &N, &M);
    
    TGraphL* graph = createGraph(N);
    TGraphL* reverse_graph = createGraph(N);
    
    for(int i = 0; i < M; i++){
        int x, y;
        fscanf(in, "%d %d", &x, &y);
        
        addEdge(graph, x, y);
        addEdge(reverse_graph, y, x);
    }
    
    printf("=== Reprezentare graph ===\n");
    printGraph(graph);
    printf("=== Reprezentare reverse_graph ===\n");
    printGraph(reverse_graph);
    
    int* visited = (int*) calloc(1 + graph -> nn, sizeof(int));
    
    for(int i = 1; i <= N; i++)
        if(!visited[i])
            dfs(graph, visited, i);
    
    for(int i = 0; i <= graph -> nn; i++)
        visited[i] = 0;
    
    int answer = 0;
    
    for(int i = N; i >= 1; i--)
        if(!visited[sol[i]])
        {
            answer++;
            dfs2(reverse_graph, visited, sol[i]);
        }
    
    printf("answer = %d \n", answer);
    
    return 0;
}
