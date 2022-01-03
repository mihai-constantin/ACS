#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Util.h"

// -----------------------------------------------------------------------------
void buildGraphsFromFile(TGraphM** gm, TGraphL** gl);
void printPath(List* path);
void printGraphMatrix(TGraphM* graph);
void printGraphList(TGraphL* graph);
// -----------------------------------------------------------------------------

#define ASSERT(cond, msg) if (!(cond)) { failed(msg); return 0; }

void passed(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t Puncte: %.2f\n", s, score);
}

void passed2(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t\t Puncte: %.2f\n", s, score);
}

void passed3(char* s, float score) {
	printf("Testul %s a fost trecut cu succes!\t\t\t Puncte: %.2f\n", s, score);
}

void failed(char* s) {
	printf("Testul %s NU a fost trecut!\n", s);
}

// -----------------------------------------------------------------------------

int testCreate(TGraphM** gm,  TGraphL** gl, float score){
	int numOfVertices;

	scanf ("%d", &numOfVertices);
	(*gm) = createGraphAdjMatrix(numOfVertices);
	ASSERT((*gm) != NULL,"Create-01");
	ASSERT((*gm)->nn == numOfVertices,"Create-02");
	ASSERT((*gm)->Ma != NULL,"Create-03");
	ASSERT((*gm)->Ma[0] != NULL,"Create-04");
	ASSERT((*gm)->Ma[1] != NULL,"Create-05");
	ASSERT((*gm)->Ma[2] != NULL,"Create-06");

	(*gl) = createGraphAdjList(numOfVertices);
	ASSERT((*gl) != NULL,"Create-07");
	ASSERT((*gl)->nn == numOfVertices,"Create-08");
	ASSERT((*gl)->adl != NULL,"Create-09");
	ASSERT((*gl)->adl[numOfVertices-1] == NULL,"Create-10");

	passed("Create",score);
	printGraphMatrix((*gm));
	printGraphList((*gl));

	return 1;
}

int testAddEdges(TGraphM** gm,  TGraphL** gl, float score){
	int v1, v2, numOfEdges;

	scanf("%d",&numOfEdges);

	for (int i=0; i < numOfEdges; i++){
		scanf("%d %d", &v1, &v2);
		addEdgeMatrix(*gm,v1,v2);
		addEdgeList(*gl,v1,v2);
	}

	ASSERT((*gm)->Ma[0][0] == 0, "AddEdges-01");
	ASSERT((*gm)->Ma[1][1] == 0, "AddEdges-02");
	ASSERT((*gm)->Ma[2][2] == 0, "AddEdges-03");
	ASSERT((*gm)->Ma[3][3] == 0, "AddEdges-04");
	ASSERT((*gm)->Ma[4][4] == 0, "AddEdges-05");
	ASSERT((*gm)->Ma[5][5] == 0, "AddEdges-06");
	ASSERT((*gm)->Ma[0][1] == 1, "AddEdges-07");
	ASSERT((*gm)->Ma[3][1] == 1, "AddEdges-08");
	ASSERT((*gm)->Ma[5][1] == 1, "AddEdges-09");
	ASSERT((*gm)->Ma[0][4] == 1, "AddEdges-10");


	ASSERT((*gl)->adl[0]->v == 4, "AddEdges-11");
	ASSERT((*gl)->adl[0]->next->v == 1, "AddEdges-12");
	ASSERT((*gl)->adl[1]->next->next->v == 2, "AddEdges-13");
	ASSERT((*gl)->adl[1]->next->v == 3, "AddEdges-14");
	ASSERT((*gl)->adl[5]->v == 1, "AddEdges-15");
	ASSERT((*gl)->adl[2]->next->v == 1, "AddEdges-16");

	passed2("Add Graph Edges", score);

	printGraphMatrix((*gm));
	printGraphList((*gl));

	return 1;
}


int testRemoveEdges(TGraphM** gm,  TGraphL** gl, float score){

	int v1 = 0, v2 = 1;

	removeEdgeMatrix((*gm),v1,v2);
	ASSERT((*gm)->Ma[v1][v2] == 0 && (*gm)->Ma[v2][v1] == 0, "RmEdges&Nodes-01");
	addEdgeMatrix((*gm),v1,v2);


	v1 = 4, v2 = 0;
	removeEdgeMatrix((*gm),v1,v2);
	ASSERT((*gm)->Ma[v1][v2] == 0 && (*gm)->Ma[v2][v1] == 0, "RmEdges&Nodes-02");
	addEdgeMatrix((*gm),v1,v2);


	v1 = 1, v2 = 3;
	removeEdgeMatrix((*gm),v2,v1);
	ASSERT((*gm)->Ma[v1][v2] == 0 && (*gm)->Ma[v2][v1] == 0, "RmEdges&Nodes-03");
	addEdgeMatrix((*gm),v1,v2);

	v1 = 3, v2 = 2;
	removeEdgeMatrix((*gm),v2,v1);
	ASSERT((*gm)->Ma[v1][v2] == 0 && (*gm)->Ma[v2][v1] == 0, "RmEdges&Nodes-04");
	addEdgeMatrix((*gm),v1,v2);

	v1 = 0, v2 = 1;
	removeEdgeList((*gl),v1,v2);
	ASSERT((*gl)->adl[v1]->v == 4 && (*gl)->adl[v2]->v == 5, "RmEdges&Nodes-05");
	addEdgeList((*gl),v1,v2);

	v1 = 2, v2 = 3;
	removeEdgeList((*gl),v1,v2);
	ASSERT((*gl)->adl[v1]->v == 1 && (*gl)->adl[v2]->next->v == 1, "RmEdges&Nodes-06");
	addEdgeList((*gl),v1,v2);

	v1 = 0, v2 = 4;
	removeEdgeList((*gl),v1,v2);
	ASSERT((*gl)->adl[v1]->v == 1 && (*gl)->adl[v2]->v == 3, "RmEdges&Nodes-07");
	addEdgeList((*gl),v1,v2);

	passed2("Remove Graph Edges", score);
	return 1;
}


int testRemoveNodes(TGraphM** gm,  TGraphL** gl, float score){

	int v,q;

	scanf ("%d", &q);
	for (int i=0; i < q; i++){
		scanf ("%d ", &v);
		removeNodeMatrix((*gm),v);
		removeNodeList((*gl),v);
	}

	ASSERT((*gm)->Ma[3][1] == 0 && (*gm)->Ma[3][1] == 0, "RmNodes-01");
	ASSERT((*gm)->Ma[0][4] == 0 && (*gm)->Ma[4][0] == 0, "RmNodes-02");
	ASSERT((*gm)->Ma[0][1] == 1 && (*gm)->Ma[1][0] == 1, "RmNodes-03");
	ASSERT((*gm)->Ma[1][2] == 1 && (*gm)->Ma[2][1] == 1, "RmNodes-04");
	ASSERT((*gm)->Ma[1][5] == 1 && (*gm)->Ma[5][1] == 1, "RmNodes-05");

	ASSERT((*gl)->adl[0]->v == 1, "RmNodes-06");
	ASSERT((*gl)->adl[1]->v == 0, "RmNodes-07");
	ASSERT((*gl)->adl[1]->next->next->v == 2, "RmNodes-08");
	ASSERT((*gl)->adl[5]->v == 1, "RmNodes-09");

	passed2("Remove Graph Nodes", score);
	printGraphMatrix((*gm));
	printGraphList((*gl));
	return 1;
}

int testDestroy(TGraphM** gm,  TGraphL** gl, float score){
	destroyGraphAdjMatrix(*gm);
	destroyGraphAdjList(*gl);
	printf(". Testul Destroy: *Se va verifica cu valgrind*\t\t\t Puncte: %.2f.\n", score);
	return 1;
}

int testDFSIterGM(TGraphM** gm,  TGraphL** gl, float score){
	List* path = dfsIterativeGM(*gm, 0);
    
    printGraphList(*gl);

	ASSERT(!isListEmpty(path),"DFSIterGM-01");
	ASSERT(path->head->next->key == 1,"DFSIterGM-02");
	ASSERT(path->head->prev->key == 0,"DFSIterGM-03");
	ASSERT(path->head->next->next->next->key == 3,"DFSIterGM-04");

	passed("DFS Iterative Adj Matrix",score);
	printPath(path);

	destroyList(path);
	return 1;
}

int testDFSRecGM(TGraphM** gm,  TGraphL** gl, float score){
	List* path = dfsRecursiveGM(*gm, 0);

	ASSERT(!isListEmpty(path),"DFSRecGM-01");
	ASSERT(path->head->next->key == 5,"DFSRecGM-02");
	ASSERT(path->head->prev->key == 0,"DFSRecGM-03");
	ASSERT(path->head->next->next->next->key == 3,"DFSRecGM-04");

	passed("DFS Recursive Adj Matrix",score);
	printPath(path);

	destroyList(path);
	return 1;
}

int testDFSRecGL(TGraphM** gm,  TGraphL** gl, float score){
	List* path = dfsRecursiveGL(*gl, 0);

	ASSERT(!isListEmpty(path),"DFSRecGL-01");
	ASSERT(path->head->next->key == 5,"DFSRecGL-02");
	ASSERT(path->head->prev->key == 0,"DFSRecGL-03");
	ASSERT(path->head->next->next->next->key == 2,"DFSRecGL-04");
	passed2("DFS Recursive Adj List",score);
	printPath(path);

	destroyList(path);
	return 1;
}

int testBFS(TGraphM** gm,  TGraphL** gl, float score){
	List* path = bfsGL(*gl, 0);

	ASSERT(!isListEmpty(path),"BFSGL-01");
	ASSERT(path->head->next->key == 2,"BFSGL-02");
	ASSERT(path->head->prev->key == 0,"BFSGL-03");
	ASSERT(path->head->next->next->next->key == 3,"BFSGL-04");
	passed3("BFS Adj List",score);
	printPath(path);
	destroyList(path);
	return 1;
}
typedef struct Test {
	int (*testFunction)(TGraphM** gm, TGraphL** gl, float);
	float score;
} Test;

int main(int argc, char* argv[]) {
	freopen ("graph.in", "r", stdin);
	Test tests[] =
	{
			{ &testCreate, 1.2 },
			{ &testAddEdges, 1.2 },
			{ &testRemoveEdges, 1.2 },
			{ &testRemoveNodes, 1.2 },
			{ &testDestroy, 1.2 },
			{ &testDFSIterGM, 1 },
			{ &testDFSRecGM, 1 },
			{ &testDFSRecGL, 1 },
			{ &testBFS, 1 }
	};

	float totalScore = 0.0f, maxScore = 0.0f;
	long testsNo = sizeof(tests) / sizeof(Test);
	long testIdx;

	TGraphM *gm;
	TGraphL *gl;


	for (testIdx = 0; testIdx < testsNo; testIdx++) {
		float score = tests[testIdx].score;
		if ((*(tests[testIdx].testFunction))(&gm,&gl, score)) {
			totalScore += score;
		}
		maxScore += score;

		if((tests[testIdx].testFunction) == testDestroy){
			gm = NULL; gl = NULL;
			fclose(stdin);
			freopen ("graph.in", "r", stdin);
			buildGraphsFromFile(&gm,&gl);
		}
	}
	printf("\nScor total: %.2f / %.2f\n\n", totalScore, maxScore);

	destroyGraphAdjMatrix(gm);
	destroyGraphAdjList(gl);
	fclose(stdin);
	return 0;
}

void buildGraphsFromFile(TGraphM** gm, TGraphL** gl){
	int numOfVertices, numOfEdges;
	int v1, v2;
	scanf ("%d", &numOfVertices);
	scanf ("%d", &numOfEdges);

	(*gm) = createGraphAdjMatrix(numOfVertices);
	(*gl) = createGraphAdjList(numOfVertices);

	for (int i = 0; i < numOfEdges; i++){
		scanf("%d %d", &v1, &v2);
		addEdgeMatrix(*gm,v1,v2);
		addEdgeList(*gl,v1,v2);
	}
}

void printPath(List* path){
	printf("Path: ");
	ListNode* it = path->head->prev;
	while(it != path->head){
		printf("%d ",it->key);
		it = it->prev;
	}
	printf("\n");
}

void printGraphMatrix(TGraphM* graph){
	printf("Graph Adjacency Matrix:\n");
	for(int i = 0; i < graph->nn; i++){
		printf("[ ");
		for(int j = 0; j < graph->nn; j++){
			printf("%d ",graph->Ma[i][j]);
		}
		printf("]\n");
	}
	printf("\n");
}


void printGraphList(TGraphL* graph){
	printf("Graph Adjacency Lists:\n");
	for(int i = 0; i < graph->nn; i++){
		printf("%2d: [ ",i);
		for(TNode* it = graph->adl[i]; it != NULL; it = it->next){
			printf("%d ", it->v);
		}
		printf("]\n");
	}
	printf("\n");
}
