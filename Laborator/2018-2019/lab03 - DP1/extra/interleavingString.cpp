#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;


class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {

    	printf("%s\n", s1.c_str());
    	printf("%s\n", s2.c_str());
    	printf("%s\n", s3.c_str());

    	s1 = " " + s1;
    	s2 = " " + s2;
    	s3 = " " + s3;

    	printf("%lu\n", s1.size());

    	int n = s1.size();
    	int m = s3.size();

    	vector<vector<int> > matrix(n);
    	for(int i = 0; i < n; i++) {
    		matrix[i] = vector<int>(m); 
    		for(int j = 0; j < m; j++) {
    			matrix[i][j] = 0;
    		}
    	} 

    	// CMLSM
    	for(int i = 1; i < n; i++) {
    		for(int j = 1; j < m; j++) {
    			if (s1.at(i) == s3.at(j)) {
    				matrix[i][j] = 1 + matrix[i - 1][j - 1];
    			}
    			else {
    				matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1]);
    			}
    		}
    	}

    	for(int i = 0; i < n; i++) {
    		for(int j = 0; j < m; j++) {
    			printf("%d ", matrix[i][j]);
    		}
    		printf("\n");
    	}

    	return false;
        
    }
};

int main() {
	Solution solution;
	string s1 = "aabcc";
	string s2 = "dbbca";
	string s3 = "aadbbcbcac";
	bool ans = solution.isInterleave(s1, s2, s3);
	printf("ans = %d\n", ans);
	return 0;
}