#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

std::vector<int> v;
int n;

void read(){
	
	int x;

	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%d", &x);
		v.push_back(x);
	}
}

int solve(){
	int s = 0;
	int maxim = v[0];
	for(int i = 0; i < v.size(); i++){
		if(v[i] > 0){
			s += v[i];
		}

		if(maxim < v[i]){
			maxim = v[i];
		}
	}

	if(s == 0){
		s = maxim;
	}

	return s;
}

void write(){
	for(int i = 0; i < v.size(); i++){
		printf("%d ", v[i]);
	}
	printf("\n");
}

int main(void){

	read();
	int s = solve();
	printf("sol = %d\n", s);

	return 0;
}