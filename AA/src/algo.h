/*
 *  Author: Constantin Mihai - 321CD
 */

#ifndef ALGO_H
#define ALGO_H

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int dmax = 1000005;
const int Log = 25;

void read();
void add(int x, int y);
void getParents();
void createMatrix();
void dfs(int node);
void query();

// bonus
std::vector<int> lca(const std::vector<std::vector<int> >& graph, const std::vector< std::pair<int, int> >& queries);

void euler(int x, const std::vector<std::vector<int> >& graph);
void RMQ();
std::vector<int> query(const std::vector< std::pair<int, int> >& queries);

// testare
void test_algo1();
void test_algo2();

#endif
