/*
 *  Solution that uses Euler Tour and RMQ.
 *  Author: Constantin Mihai - 321CD
 */

#include <iostream>
#include <cstdio>
#include <time.h>
#include <cmath>
#include <fstream>
#include "algo.h"
using namespace std;

int level[dmax];
bool visited[dmax];

int E[2 * dmax - 1]; // E[i] = the label of i-th visited node in the Euler tour
int L[2 * dmax - 1]; // L[i] = the level of node E[i]
int K;

int H[dmax]; // H[i] = the index of the first occurance of node i in E

int rmq[2 * dmax - 1][Log];
int lg[2 * dmax - 1];

int N; // number of nodes
int M; // number of edges

void euler(int x, const std::vector< std::vector<int> >& graph){
    
    visited[x] = true;
    E[++K] = x;
    
    if(!H[x]){
        H[x] = K;
    }
    
    for(unsigned long i = 0; i < graph[x].size(); i++){
        int y = graph[x][i];
        
        if(!visited[y]){
            /* get the level for every node */
            level[y] = 1 + level[x];
            euler(y, graph);
            E[++K] = x;
        }
    }
}

void RMQ(){
    for(int i = 1; i <= K; i++){
        L[i] = level[E[i]];
    }
    
    lg[1] = 0;
    for(int i = 2; i <= K; i++){
        lg[i] = lg[i/2] + 1;
    }
    
    for(int i = 1; i <= K; i++){
        rmq[i][0] = i;
    }
    
    for(int i = 1; i <= K; i++){
        for(int j = 1; (1 << j) <= i; j++){
            int k = i - (1 << (j - 1));
            
            rmq[i][j] = rmq[i][j - 1];
            
            if(L[rmq[k][j - 1]] < L[rmq[i][j]]){
                rmq[i][j] = rmq[k][j - 1];
            }
        }
    }
}

std::vector<int> query(const std::vector< std::pair<int, int> >& queries){
    
    std::vector<int> answer;
    
    int p, q;
    for(unsigned long i = 0; i < queries.size(); i++){
        p = queries[i].first;
        q = queries[i].second;
        
        p = H[p];
        q = H[q];
        
        if(p > q){
            swap(p, q);
        }
        
        int l = lg[q - p + 1];
        int ans = rmq[q][l];
        
        if(L[rmq[p + (1 << l) - 1][l]] < L[ans]){
            ans = rmq[p + (1 << l) - 1][l];
        }
        
        answer.push_back(E[ans]);
    }
    
    return answer;
}

std::vector<int> lca(const std::vector< std::vector<int> >& graph, const std::vector< std::pair<int, int> >& queries) {
    
    euler(1, graph);
    RMQ();
    
    std::vector<int> answer = query(queries);
    return answer;
}

void test_algo1(){
    
   	ifstream in("lca.in");
    ofstream out("lca.out");
    ofstream out_time("time.out");

    clock_t t = clock();
    
    std::vector< std::vector<int> > graph;
    std::vector< std::pair<int, int> > queries;
    
    in >> N >> M;
    
    graph.resize(N + 1);
    
    int x, y;
    for(int i = 1; i <= N - 1; i++){
        in >> x >> y;
        graph[x].push_back(y);
    }
    
    for(int i = 1; i <= M; i++){
        in >> x >> y;
        queries.push_back(make_pair(x, y));
    }
    
    std::vector<int> v = lca(graph, queries);
    
    for(unsigned long i = 0; i < v.size(); i++){
        out << v[i] << '\n';
    }
    
    t = clock() - t;
    float time = ((float)t)/CLOCKS_PER_SEC;
    printf ("Processor time consumed by the program: %f seconds.\n", time);

    out_time << time << '\n';
}
