#include <iostream>
#include <cstdio>
#include <stack>
#include <set>
#include <vector>

using namespace std;

#define dmax 100002

vector<int> graph[dmax];
int n, m;

vector<int> idx;
vector<int> lowlink;
vector<int> parent;
int indecs;

typedef struct Edge {
	int x;
	int y;
} Edge;

stack <Edge> S;

set<int> comp; 
vector< set<int> >sol;
int nr_comp;

FILE *in, *out;

void print_component() {
    sol.push_back(comp);
}

void print_set(set<int> componenta) {
	set <int> :: iterator itr; 
    for (itr = componenta.begin(); itr != componenta.end(); ++itr) 
    { 
        fprintf(out, "%d ", *itr);
    }
    fprintf(out, "\n"); 
}

void biconnected_components(int x) {

	int children, i, y, tx, ty;
	Edge edge;
	idx[x] = lowlink[x] = ++indecs;
	children = 0;

	// parcurg vecinii y ai lui x
	for(i = 0; i < graph[x].size(); i++) {
		y = graph[x][i];

		if(idx[y] == -1) {
			children++;
			parent[y] = x;

			// store the edge in stack
			edge.x = x;
			edge.y = y;
			S.push(edge);
			biconnected_components(y);

			lowlink[x] = min(lowlink[x], lowlink[y]);

			if((idx[x] == 1 && children > 1) || (idx[x] > 1 && lowlink[y] >= idx[x])) {
				nr_comp++;
				while(S.top().x != x || S.top().y != y) {
					tx = S.top().x;
					ty = S.top().y;
					// cout << tx << "--" << ty << " ";
					comp.insert(tx);
					comp.insert(ty);
					S.pop();
				} 

				tx = S.top().x;
				ty = S.top().y;
				comp.insert(tx);
				comp.insert(ty);
				// cout << tx << "--" << ty;
				S.pop();

				print_component();
				comp.clear();

				// cout << '\n';
			}

		}
		else {
			if(parent[x] != y) {
				lowlink[x] = min(lowlink[x], idx[y]);

				if(idx[y] < idx[x]) {
					edge.x = x;
					edge.y = y;
					S.push(edge);
				}
			}
		}
	}
}

int main()
{
	in = fopen("biconex.in", "r");
	out = fopen("biconex.out", "w");

	int i, x, y, tx, ty;

	fscanf(in, "%d %d", &n, &m);
	for(i = 1; i <= m; i++) {
		fscanf(in, "%d %d", &x, &y);
		// graf neorientat
		graph[x].push_back(y);
		graph[y].push_back(x);

	}

	idx.resize(n + 1);
	idx.assign(n + 1, -1);

	lowlink.resize(n + 1);
	parent.resize(n + 1);

	for(i = 1; i <= n; i++) {
		if(idx[i] == -1) {
			biconnected_components(i);
		}

		bool ok = false;
		while(S.size() > 0) {
			nr_comp++;
			ok = true;
			// cout << S.top().x << "--" << S.top().y << " ";
			tx = S.top().x;
			ty = S.top().y;
			comp.insert(tx);
			comp.insert(ty);
			S.pop();
		}

		if(ok) {
			print_component();
			comp.clear();
			// cout << "\n";
		}		
	}

	fprintf(out, "%lu\n", sol.size());
	for(i = 0; i < sol.size(); i++) {
		print_set(sol[i]);
	}
	

	return 0;
}