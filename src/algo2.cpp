/*
 *  Solution that uses dynamic programming.
 *  Author: Constantin Mihai - 321CD
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "algo.h"
using namespace std;

ifstream in ("lca.in");
ofstream out ("lca.out");
ofstream out_time("time.out");

int A[Log][dmax]; // A[i][j] = 2^i-th ancestor of j

int level[dmax];
bool visited[dmax];

int parent[dmax];

vector <int> graph[dmax];

int N; // number of nodes
int M; // number of edges

void getParents(){
    for(int x = 1; x <= N; x++){
        for(unsigned long i = 0; i < graph[x].size(); i++){
            parent[graph[x][i]] = x;
        }
    }
}

void createMatrix(){
    
    /* Create matrix A */
    
    for(int i = 2; i <= N; ++i){
        /* the first ancestor of every node i is his parent */
        A[0][i] = parent[i];
    }
    
    /* dynamic programming */
    for(int k = 1; (1 << k) <= N; ++k) {
        for(int i = 1; i <= N; ++i) {
            A[k][i] = A[k-1][A[k-1][i]];
        }
    }
}

void add(int x, int y){
    // add y in the x's list
    graph[x].push_back(y);
}

void read()
{
    in >> N >> M;
    
    int x, y;
    for(int i = 2; i <= N; ++i){
        in >> x >> y;
        add(x, y);
    }
}

void dfs(int node){
    
    visited[node] = true;
    
    for(unsigned long i = 0; i < graph[node].size(); i++){
        int y = graph[node][i];
        
        if(!visited[y]){
            /* get the level for every node */
            level[y] = 1+ level[node];
            dfs(y);
        }
    }
}

int lca(int x, int y)
{
    /* if x is situated on a higher level than y then we swap them */
    if(level[x] < level[y])
        swap(x, y);
    
    int log1;
    /* compute the value of [log(level[x])]*/
    for(log1 = 1; (1 << log1) < level[x]; ++log1);
    
    int log2;
    /* compute the value of [log(level[y])]*/
    for(log2 = 1; (1 << log2) < level[y]; ++log2);
    
    for(int k = log1; k >= 0; --k)
        if(level[x] - (1 << k) >= level[y])
            x = A[k][x];
    
    if(x == y)
        return x;
    
    /* here, x and y are situated on the same level */
    for(int k = log2; k >= 0; --k)
        if(A[k][x] && A[k][x] != A[k][y])
            x = A[k][x],
            y = A[k][y];
    
    /* here, lca(x, y) = parent[x] */
    return A[0][x];
}

void query(){
    for(int i = 1; i <= M; i++){
        int x, y;
        in >> x >> y;
        out << lca(x, y) << "\n";
    }
}

void test_algo2(){
    
    clock_t t = clock();
    
    read();
    getParents();
    
    createMatrix();
    
    dfs(1);
    query();
    
    t = clock() - t;
    float time = ((float)t)/CLOCKS_PER_SEC;
    printf ("Processor time consumed by the program: %f seconds.\n", time);
    
    out_time << time << '\n';
}
