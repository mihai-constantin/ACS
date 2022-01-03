#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

struct Object{
	int valueNow;
	int valueNextWeek;
	Object(int _valueNow, int _valueNextWeek) : valueNow(_valueNow), valueNextWeek(_valueNextWeek) {}
};

bool cmp(Object obj1, Object obj2) {
	int dif1 = obj1.valueNow - obj1.valueNextWeek;
	int dif2 = obj2.valueNow - obj2.valueNextWeek;

	if(dif1 == dif2) {
		return obj1.valueNow > obj2.valueNow;
	}
	return dif1 < dif2;
}

int main(void) 
{
	int n, k, x, i, j;

	std::vector<Object> objs;
	std::vector<int> priceNow;
	std::vector<int> priceNextWeek;

	scanf("%d %d", &n, &k);

	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		priceNow.push_back(x);
	}

	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		priceNextWeek.push_back(x);
	}

	for(i = 0; i < n; i++) {
		objs.push_back(Object(priceNow[i], priceNextWeek[i]));
	}

	sort(objs.begin(), objs.end(), cmp);

	int money = 0;
	// aleg primele k produse
	for(i = 0; i < k; i++) {
		money += objs[i].valueNow;
	}

	// aleg mai mult de k produse daca am profit
	for(i = k; i < objs.size() && objs[i].valueNow < objs[i].valueNextWeek; i++) {
		money += objs[i].valueNow;
	}

	// aleg restul produselor
	for(j = i; j < objs.size(); j++){
		money += objs[j].valueNextWeek;
	}

	printf("%d\n", money);

	return 0;
}
