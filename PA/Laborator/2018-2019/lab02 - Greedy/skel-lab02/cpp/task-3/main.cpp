#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

struct Homework {
	int deadline;
	int score;

	Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

bool cmp(Homework hw1, Homework hw2) {
	if(hw1.deadline == hw2.deadline){
		return hw1.score < hw2.score;
	}
	return hw1.deadline < hw2.deadline;
}

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<Homework> hws;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, deadline, score; i < n; i++) {
			fin >> deadline >> score;
			hws.push_back(Homework(deadline, score));
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Aflati punctajul maxim pe care il puteti obtine planificand
		optim temele.
		*/

		sort(hws.begin(), hws.end(), cmp);
		// for(int i = 0; i < hws.size(); i++) {
		// 	cout << hws[i].deadline << " " << hws[i].score << '\n';
		// }

		std::vector<int> scores(hws[hws.size() - 1].deadline + 1, 0);

		scores[scores.size() - 1] = hws[hws.size() - 1].score;
		hws[hws.size() - 1].score = -1;

		for(int i = scores.size() - 2; i > 0; i--) {
			// gasesc scorul pentru week i
			int maxim = 0;
			int pos = 0;
			for(int j = hws.size() - 1; j >= 0; j--) {

				if(hws[j].deadline < i) {
					break;
				}

				if(hws[j].score != -1) {
					if(maxim < hws[j].score) {
						maxim = hws[j].score;
						pos = j;
					}
				}
			}

			if(maxim != 0){
				scores[i] = maxim;
				hws[pos].score = -1;
			}	
		}

		int res = 0;
		for(int i = 1; i < scores.size(); i++) {
			res += scores[i];
		}

		return res;

	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << "\n";
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}