#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

#define INF 1000002

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}


void dijkstra(TGraphL G, int s)
{
    int* d = (int*) malloc(G.nn * sizeof(int));
    
    for(int i = 0; i < G.nn; i++)
        d[i] = INF;
    
    /* creare MinHeap */
    MinHeap* h = newQueue(G.nn);
    
    /* creare && initializare vector visited */
    int* visited = (int*) malloc(G.nn * sizeof(int));
    for(int i = 0; i < G.nn; i++)
        visited[i] = 0;
    
    MinHeapNode* node = NULL;
    
    for(int i = 0; i < G.nn; i++)
        h -> pos[i] = i;
    
    /* inserez nodul de start */
    h -> pos[s] = s;
    d[s] = 0;
    SiftUp(h, s, 0);
    
    while(!isEmpty(h))
    {
        while (!isEmpty(h) && visited[h -> elem[0] -> v]) {
            node = removeMin(h);
        }
        
        if(isEmpty(h))
            break;
        
        node = removeMin(h);
        visited[node -> v] = 1;
        
        /* parcurg vecinii nodului node */
        TNode* iterator = G.adl[node -> v];
        
        while(iterator != NULL)
        {
            int y = iterator -> v;
            int cost = iterator -> c;
            
            if(d[y] > d[node -> v] + cost && !visited[y])
            {
                d[y] = d[node -> v] + cost;
                SiftUp(h, y, d[y]);
            }
            
            iterator = iterator -> next;
        }
    }
    
    for(int i = 0; i < G.nn; i++)
        printf("%d %d\n", i, d[i]);
}

void Prim(TGraphL G)
{
    int* d = (int*) malloc(G.nn * sizeof(int));
    
    for(int i = 0; i < G.nn; i++)
        d[i] = INF;
    
    /* creare MinHeap */
    MinHeap* h = newQueue(G.nn);
    
    /* creare && initializare vector visited */
    int* visited = (int*) malloc(G.nn * sizeof(int));
    for(int i = 0; i < G.nn; i++)
        visited[i] = 0;
    
    /* creare && initializare vector parent */
    int* parent = (int*) malloc(G.nn * sizeof(int));
    for(int i = 0; i < G.nn; i++)
        parent[i] = -1;
    
    MinHeapNode* node = NULL;
    
    for(int i = 0; i < G.nn; i++)
        h -> pos[i] = i;
    
    /* inserez nodul de start */
    h -> pos[0] = 0;
    d[0] = 0;
    SiftUp(h, 0, 0);
    
    while(!isEmpty(h))
    {
        while (!isEmpty(h) && visited[h -> elem[0] -> v]) {
            node = removeMin(h);
        }
        
        if(isEmpty(h))
            break;
        
        node = removeMin(h);
        
        visited[node -> v] = 1;
        
        /* parcurg vecinii nodului node */
        TNode* iterator = G.adl[node -> v];
        
        while(iterator != NULL)
        {
            int y = iterator -> v;
            int cost = iterator -> c;
            
            if(d[y] > cost && visited[y] == 0)
            {
                parent[y] = node -> v;
                d[y] = cost;
                SiftUp(h, y, d[y]);
            }
            
            iterator = iterator -> next;
        }
    }
    
    for(int i = 0; i < G.nn; i++)
        printf("%d %d\n", parent[i], i);
    
    /* vreau sa determin costul minim */
    
    
    
}


int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    printf("%d : ", i);
    for(t = G.adl[i]; t != NULL; t = t->next)
    printf("%d ",t->v);
    printf("\n");
	}
	dijkstra(G,0);
	Prim(G);

	return 0;
}
