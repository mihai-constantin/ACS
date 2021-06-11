#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

#define dmax 100005
vector<int> graph[dmax];
int n, m;

vector<int> idx;
vector<int> lowlink;
vector<int> in_stack;
int indecs;

stack <int> S;

vector<vector<int> > sol;
vector<int> comp;

FILE *in, *out;

void tarjan(int x) {

	int i, y, node;

	idx[x] = lowlink[x] = indecs++;
	// introducem nodul in stiva
	S.push(x);
	// marcam nodul x ca fiind in stiva
	in_stack[x] = 1;

	// parcurgem vecinii y ai lui x
	for(i = 0; i < graph[x].size(); i++) {
		y = graph[x][i];

		if(idx[y] == -1) {
			tarjan(y);
			lowlink[x] = min(lowlink[x], lowlink[y]);
		}
		else {
			if(in_stack[y]) {
				lowlink[x] = min(lowlink[x], lowlink[y]);
			}
		}
	}

	if(idx[x] == lowlink[x]) {
		// am gasit o componenta tare conexa
		comp.clear();
		do
		{	
			node = S.top();
			comp.push_back(node);
			S.pop();
			in_stack[node] = 0;
		}while(x != node);

		sol.push_back(comp);
	}
}

void showstack(stack <int> s) 
{ 
    while (!s.empty()) 
    { 
        cout << s.top() << " "; 
        s.pop(); 
    } 
    cout << '\n'; 
} 

int main(void)
{
	in = fopen("tarjan.in", "r");
	out = fopen("tarjan.out", "w");

	int i, j, x, y;

	fscanf(in, "%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		fscanf(in, "%d %d", &x, &y);
		graph[x].push_back(y); // graf orientat
	}

	// afisare graf
	for(x = 1; x <= n; x++) {
		printf("%d: ", x);

		// parcurg vecinii nodului x
		for(i = 0; i < graph[x].size(); i++) {
			y = graph[x][i];
			printf("%d ", y);
		}
		printf("\n");
	}

	printf("----------------------\n");


	idx.resize(n + 1); 
	idx.assign(n + 1, -1);
	lowlink.resize(n + 1);
	in_stack.resize(n + 1);
	in_stack.assign(n + 1, 0);

	// for(i = 1; i <= n; i++) {
	// 	if(idx[i] == -1) {
	// 		tarjan(i);
	// 	}
	// }

	tarjan(1);
	// tarjan(6);
	// tarjan(9);
	// tarjan(11);

	printf("idx: ");
	for(i = 1; i <= n; i++) {
		printf("%d ", idx[i]);
	}
	printf("\n");

	printf("lowlink: ");
	for(i = 1; i <= n; i++) {
		printf("%d ", lowlink[i]);
	}
	printf("\n");

	printf("in_stack: ");
	for(i = 1; i <= n; i++) {
		printf("%d ", in_stack[i]);
	}
	printf("\n");

	printf("stack: ");
	showstack(S);

	printf("------------------\n");

	printf("%lu\n", sol.size());
	for(i = 0; i < sol.size(); i++) {
		// afisez componenta i
		for(j = 0; j < sol[i].size(); j++) {
			y = sol[i][j];
			printf("%d ", y);
		}
		printf("\n");
	}



	return 0;
}