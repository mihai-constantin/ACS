// Mihai Constantin 2021
// Varianta optima rucsac discret - recurenta vectoriala
#include <iostream>
#include <cstdio>
using namespace std;

#define Nmax 5002
#define Gmax 10002

struct obj {
	int weight;
	int price;
};

int profit[Gmax];

obj v[Nmax];
int N, G;

int main(void) 
{
	freopen("rucsac.in", "r", stdin);
	freopen("rucsac.out", "w", stdout);

	scanf("%d %d", &N, &G);
	for(int i = 0; i < N; i++) {
		scanf("%d %d", &v[i].weight, &v[i].price);
	}

	profit[0] = 0;
	for(int i = 1; i <= G; i++) {
		profit[i] = -1;
	}

	for(int i = 0; i < N; i++) {
		for(int j = G; j >= v[i].weight; j--) {
			if(profit[j - v[i].weight] != -1 && profit[j - v[i].weight] + v[i].price > profit[j]) {
				profit[j] = profit[j - v[i].weight] + v[i].price;
			}
		}
	}

	int profit_maxim = profit[0];
	for(int i = 1; i <= G; i++) {
		if(profit[i] > profit_maxim) {
			profit_maxim = profit[i];
		}
	}
	printf("%d\n", profit_maxim);

	return 0;
}
