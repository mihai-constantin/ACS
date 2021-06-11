#include <iostream>
#include <vector>
using namespace std;

vector<int> v;

int binary_search(int st, int dr, int k) {
  if (dr < st) {
    return -1;
  }

  int m = (st + dr)/2;
  if (v[m] == k) {
    return m;
  }
  if (v[m] < k) {
    return binary_search(m + 1, dr, k);
  }
  return binary_search(st, m - 1, k);
}

int main()
{
  for (int i = 0; i < 10; i++) {
    v.push_back(i);
  }

  cout << binary_search(0, 10, 4) << '\n'; // 4
  cout << binary_search(0, 10, 15) << '\n'; // -1

  return 0;
}