/*
 * graph.h
 *
 *  Created on: May 9, 2016
 *      Author: dan
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include "Util.h"

typedef int TCost; // Cost(weight) of path to a specific node (NOT USED IN THIS LAB)

typedef struct{
	int nn; // Number of nodes in the graph
	int **Ma; // Adjancey  matrix
}TGraphM;

typedef struct TNode{
	int v; // Destination node index
	TCost c; // Cost of the edge associated with the nodes - (NOT USED IN THIS LAB)
	struct TNode *next; // Link to the next node in the list
}TNode, *ATNode;

typedef struct{
	int nn; // Number of nodes in the graph
	ATNode *adl; // Adjancey list (TNode**)
}TGraphL;


TGraphM* createGraphAdjMatrix(int numberOfNodes);
TGraphL* createGraphAdjList(int numberOfNodes);

void addEdgeMatrix(TGraphM* graph, int v1, int v2);
void addEdgeList(TGraphL* graph, int v1, int v2);
void removeEdgeMatrix(TGraphM* graph, int v1, int v2);
void removeNodeMatrix(TGraphM* graph, int v);
void removeEdgeList(TGraphL* graph, int v1, int v2);
void removeNodeList(TGraphL* graph, int v);

List* dfsIterativeGM(TGraphM* graph, int s);
List* dfsRecursiveGM(TGraphM* G, int s);
List* dfsRecursiveGL(TGraphL* G, int s);
List* bfsGL(TGraphL* graph, int s);

void destroyGraphAdjMatrix(TGraphM *graph);
void destroyGraphAdjList(TGraphL* graph);


#endif /* GRAPH_H_ */
