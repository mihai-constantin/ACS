#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){

	freopen("cuie.in", "r", stdin);
	freopen("cuie.out", "w", stdout);

	std::vector<pair<int, int> > v;

	int n;

	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		pair<int, int> p;
		scanf("%d %d", &p.first, &p.second);
		v.push_back(p);
	}

	sort(v.begin(), v.end());

	for(int i = 0; i < v.size(); i++){
		printf("%d %d\n", v[i].first, v[i].second);
	}

	int res = 1;
	int dr = v[0].second;
	for(int i = 1; i < v.size(); i++){
		if(v[i].first > dr){
			res++;
			dr = v[i].second;
		}
	}

	printf("res = %d\n", res);

	return 0;
}