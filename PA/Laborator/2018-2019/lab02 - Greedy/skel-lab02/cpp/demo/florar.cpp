#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;



int main(void){

	int k; // numar oameni
	int n; // numar flori

	std::vector<int> cost;

	int x;
	scanf("%d %d", &k, &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &x);
		cost.push_back(x);
	}

	sort(cost.begin(), cost.end(), greater<int>()); 

	for(int i = 0; i < cost.size(); i++){
		printf("%d ", cost[i]);
	}
	printf("\n");

	int res = 0;
	int cnt = 0;

	x = 0;
	for(int i = 0; i < cost.size(); i++){
		cnt++;
		res += (x + 1) * cost[i];

		if(cnt == k){
			x++;
			cnt = 0;
		}
	}

	printf("cost minim = %d\n", res);

	return 0;
}