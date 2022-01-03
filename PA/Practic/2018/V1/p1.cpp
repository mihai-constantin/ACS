#include <iostream>
#include <cstdio>
using namespace std;

#define dmax 10005

int v[dmax];
int N;

int main() {
	
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);

	int i, maxim = 0, minim = 0;

	scanf("%d", &N);
	for(i = 1; i <= N; i++) {
		scanf("%d", &v[i]);
		if(v[i] == 1) {
			maxim++;
		}
	}

	i = 1;
	while(i <= N) {
		if(v[i] == 1) {
			minim++;
			i += 3;
		}
		else {
			i++;
		}
	}

	printf("%d %d\n", minim, maxim);

    return 0;
}