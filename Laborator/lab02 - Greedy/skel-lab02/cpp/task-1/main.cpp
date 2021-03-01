#include <fstream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Object {
	int weight;
	int price;

	Object(int _weight, int _price) : weight(_weight), price(_price) {}
};

bool cmp(Object obj1, Object obj2) {

	double value1 = (double)obj1.price / (double)obj1.weight;
	double value2 = (double)obj2.price / (double)obj2.weight;

	return value1 > value2;
}

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, w;
	vector<Object> objs;

	void read_input() {
		ifstream fin("in");
		fin >> n >> w;
		for (int i = 0, weight, price; i < n; i++) {
			fin >> weight >> price;
			objs.push_back(Object(weight, price));
		}
		fin.close();
	}

	double get_result() {
		/*
		TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
		*/

		sort(objs.begin(), objs.end(), cmp);

		for(int i = 0; i < objs.size(); i++){
			cout << objs[i].weight << " " << objs[i].price << '\n';
		}

		double ans = 0;
		for(int i = 0; i < objs.size(); i++){
			Object obj = objs[i];
			if(obj.weight <= w){
				// iau tot obiectul
				ans += obj.price;
				w -= obj.weight;
			}
			else{
				ans += w * ((double)obj.price / (double)obj.weight);
				w = 0;
			}

			if(w == 0){
				break;
			}
		}

		return ans;
	}

	void print_output(double result) {
		ofstream fout("out");
		fout << setprecision(4) << fixed << result << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}