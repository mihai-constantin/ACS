#include <cmath>
#include <cstdio>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

ifstream in("in");

#define dmax 200005
#define Lmax 30

char st[dmax];
char dr[dmax];
int N;

int f_st[Lmax];
int f_dr[Lmax];

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

	int i, star_st = 0, star_dr = 0;

	in >> N;
	in >> st;
	in >> dr;

	int length_st = strlen(st);
	for(i = 0; i < length_st; i++) {
		
		if(st[i] >= 'a' && st[i] <= 'z') {
				f_st[st[i] - 97]++;
		}
		else {
			star_st++;
		}
	}

	int length_dr = strlen(dr);
	for(i = 0; i < length_dr; i++) {
		
		if(dr[i] >= 'a' && dr[i] <= 'z') {
			f_dr[dr[i] - 97]++;
		}
		else {
			star_dr++;
		}
	}

	int answer = 0, fmin;
	for(i = 0; i <= 25; i++) {
		fmin = min(f_st[i], f_dr[i]);
		answer += fmin;
		f_st[i] -= fmin;
		f_dr[i] -= fmin;
	}

	// for(i = 0; i <= 25; i++) {
	// 	cout << (char) (i + 97) << " " << f_st[i] << '\n' ;
	// }
	// cout << "----------\n";

	// for(i = 0; i <= 25; i++) {
	// 	cout << (char) (i + 97) << " " << f_dr[i] << '\n' ;
	// }
	// cout << "----------\n";

	// cout << star_st << " " << star_dr << '\n';

	// asociez litere din st cu * din dr
	for(i = 0; i <= 25; i++) {
		if(f_st[i] > 0) {
			fmin = min(f_st[i], star_dr);
			answer += fmin;
			f_st[i] -= fmin;
			star_dr -= fmin;
		}
	}

	// asociez literele din dr cu * din st
	for(i = 0; i <= 25; i++) {
		if(f_dr[i] > 0) {
			fmin = min(f_dr[i], star_st);
			answer += fmin;
			f_dr[i] -= fmin;
			star_st -= fmin;
		}
	}

	if(star_st > 0 && star_dr > 0) {
		cout << answer + min(star_st, star_dr) << '\n';
	}
	else {
		cout << answer << '\n';
	}

    return 0;
}