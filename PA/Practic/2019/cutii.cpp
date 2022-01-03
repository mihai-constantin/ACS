#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int N, K;

double calculate(double initialProbability) {

	double s = 0;
	for(int i = 1; i <= N; i++) {
		s += i * initialProbability;
	}

	return s;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
  
	int i;

    scanf("%d %d", &N, &K);
    
    if(K == 0) {

        printf("%.9lf\n", (double)(N));
    }
    else {
        
        double initialProbability = 1 / (double)(N);
        double ans;

        for(i = 1; i <= K; i++) {
        	ans = calculate(initialProbability);
        	initialProbability = ans;
        }
        printf("%.9lf\n", ans); 
    }
    
    return 0;
}