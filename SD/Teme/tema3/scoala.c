#include <stdio.h>
#include <stdlib.h>

typedef struct TNode{
    int v;
    struct TNode* next;
}TNode;

typedef struct {
    int nn; /* numberofNodes */
    TNode** adl; /* adjancey  list */
}TGraph;

TGraph* createGraphAdjList(int numberofNodes)
{
    /* aloc memorie pentru o structura de tip TGraph */
    TGraph* graph = (TGraph*) malloc(sizeof(TGraph));
    
    if(!graph)
        return NULL;
    
    graph -> nn = numberofNodes;
    
    /* aloc memorie pentru listele de adiacenta */
    graph -> adl = (TNode**) malloc((1 + numberofNodes) * sizeof(TNode*));
    
    /* setez la NULL fiecare lista de adiacenta */
    for(int i = 0; i <= numberofNodes; i++)
        graph -> adl[i] = NULL;
    
    return graph;
}

void addEdgeList(TGraph* graph, int x, int y)
{
    /* adaug in graf muchia x - y */
    TNode* node_1 = (TNode*) malloc(sizeof(TNode));
    
    node_1 -> v = y;
    node_1 -> next = graph -> adl[x];
    
    graph -> adl[x] = node_1;
}

void dfsRecursiveGL(FILE* out, TGraph* graph, int* visited, int node)
{
    visited[node] = 1;
    
    /* parcurg vecinii nodului node */
    TNode* iterator = graph -> adl[node];
    
    while (iterator)
    {
        if(!visited[iterator -> v])
            dfsRecursiveGL(out, graph, visited, iterator -> v);
        
        iterator = iterator -> next;
    }
}

void destroy(TGraph* graph)
{
    if(!graph)
        return;
    
    for(int i = 0; i <= graph -> nn; i++)
    {
        TNode* iterator = graph -> adl[i];
        
        while(iterator)
        {
            TNode* aux = iterator;
            iterator = iterator -> next;
            free(aux);
        }
    }
    
    free(graph -> adl);
    free(graph);
    graph = NULL;
}

int main()
{
    FILE *in, *out;
    
    in = fopen("scoala.in", "r");
    out = fopen("scoala.out", "w");
    
    int numberofTests;
    fscanf(in, "%d", &numberofTests);
    
    int numberOfNodes, numberOfEdges, c_drum, c_sc;
    int x, y, cost;
    
    for(int i = 0; i < numberofTests; i++)
    {
        fscanf(in, "%d %d %d %d", &numberOfNodes, &numberOfEdges, &c_drum, &c_sc);
        
        TGraph* graph = createGraphAdjList(numberOfNodes);
        
        for(int j = 0; j < numberOfEdges; j++)
        {
            fscanf(in, "%d %d", &x, &y);
            /* graf neorientat */
            addEdgeList(graph, x, y);
            addEdgeList(graph, y, x);
        }
        
        int* visited = (int*) malloc((1 + numberOfNodes) * sizeof(int));
        /* initializare visited */
        for(int i = 0; i <= numberOfNodes; i++)
            visited[i] = 0;
        
        int numberOfComponents = 0; /* nr de componente conexe din graf */
        
        for(int i = 1; i <= numberOfNodes; i++)
            if(!visited[i])
            {
                numberOfComponents++;
                dfsRecursiveGL(out, graph, visited, i);
            }
        
        if(c_drum >= c_sc) /* nu are rost sa repar drumuri -> construiesc o scoala in fiecare nod */
            cost = numberOfNodes * c_sc;
        else  /* repar drumuri + construiesc o scoala in fiecare componenta conexa */
            cost = numberOfComponents * c_sc + ((graph -> nn) - numberOfComponents) * c_drum;
        
        fprintf(out, "%d\n", cost);
        
        TGraph* aux = graph;
        destroy(aux);
        
        int* Aux = visited;
        free(Aux);
    }
    
    fclose(in);
    fclose(out);
    
    return 0;
}
