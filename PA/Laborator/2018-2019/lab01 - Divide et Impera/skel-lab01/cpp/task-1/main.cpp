#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(get_result());
	}

private:
	int n, x;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, e; i < n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin >> x;
		fin.close();
	}

	int find_first() {
		/*
		TODO: Cautati prima pozitie pe care se afla valoarea x
		In cazul in care x nu apare in sir, returnati -1
		*/
		int first_pos = -1, left, right, mid;
		left = 0;
		right = v.size() - 1;
		while(left <= right){
		    mid = (left + right) / 2;
		    if(v[mid] >= x){
		        first_pos = mid;
		        right = mid - 1;
		    }
		    else{
		        left = mid + 1;
		    }
		}
		return first_pos;
	}

	int find_last() {
		/*
		TODO: Cautati ultima pozitie pe care se afla valoarea x
		In cazul in care x nu apare in sir, returnati -1
		*/
		int last_pos = -1, left, right, mid;
		left = 0;
		right = v.size() - 1;
		while(left <= right){
		    mid = (left + right) / 2;
		    if(v[mid] <= x){
		        last_pos = mid;
		        left = mid + 1;
		    }
		    else{
		        right = mid - 1;
		    }
		}
		return last_pos;
	}

	int get_result() {
		// TODO: Calculati numarul de aparitii ale lui x in vectorul v
		int first_pos = find_first();
		int last_pos = find_last();
		if(first_pos == -1 || last_pos == -1){
		    return 0;
		}
		return last_pos - first_pos + 1;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
