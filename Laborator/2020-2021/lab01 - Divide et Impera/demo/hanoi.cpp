#include <iostream>
#include <string>
using namespace std;

void hanoi(int n, string source, string dest, string aux)  { 
	if (n == 1) { 
  	cout << "Mut discul " << n << " de pe tija " << source << " pe tija " << dest << '\n';
		return; 
	} 
	hanoi(n - 1, source, aux, dest); 
	cout << "Mut discul " << n << " de pe tija " << source << " pe tija " << dest << '\n';
	hanoi(n - 1, aux, dest, source); 
} 

int main() 
{ 
	int n = 4;
	hanoi(n, "S", "D", "aux");
	return 0; 
} 
