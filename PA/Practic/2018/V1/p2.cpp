#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

#define dmax 1000005

char s[dmax];

int main() {
	/* Cititi de la STDIN si afisati la STDOUT. Decomentati linia de mai jos daca
     * folositi cin/cout. Nu imbinati cin/cout cu scanf/printf in acest caz.
     */
	// ios::sync_with_stdio(false);

	int i, length;

	freopen("in", "r", stdin);

	scanf("%s", s);

	length = strlen(s);

	if(length == 1 && s[0] == '_') {
		s[0] = 'a';
		cout << s << '\n';
		return 0;

	}

	if(s[0] == '_') {
		if(s[1] == 'a') {
			s[0] = 'b';
		}
		else {
			s[0] = 'a';
		}
	}

	char st, dr;
	for(i = 1; i < length - 1; i++) {
		if(s[i] == '_') {
			st = s[i - 1];
			dr = s[i + 1];

			if(st != 'a' && dr != 'a') {
				s[i] = 'a';
			}
			else {
				if(st != 'b' && dr != 'b') {
					s[i] = 'b';
				}
				else {
					s[i] = 'c';
				}
			}

		}
	}

	if(s[length - 1] == '_') {
		if(s[length - 2] != 'a') {
			s[length - 1] = 'a';
		}
		else {
			s[length - 1] = 'b';
		}
	}

	cout << s << '\n';

    return 0;
}