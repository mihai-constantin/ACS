#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("spectacole.in");
ofstream out("spectacole.out");

bool sortbysec(const pair<int, int> &a, const pair <int, int> &b){
	if(a.second == b.second){
		return a.first < b.first;
	}
	return a.second < b.second;
}

int main(void){

	unsigned int n, x, y;
	vector< pair<int, int> > v;

	in >> n;
	for(unsigned int i = 0; i < n; i++){
		in >> x >> y;
		v.push_back(make_pair(x, y));
	}

	sort(v.begin(), v.end(), sortbysec);

	int res = 1;
	int pos = 0;
	for(unsigned int i = 1; i < v.size(); i++){
		if(v[i].first >= v[pos].second){
			res++;
			pos = i;
		}
	}

	out << res << '\n';

	return 0;
}