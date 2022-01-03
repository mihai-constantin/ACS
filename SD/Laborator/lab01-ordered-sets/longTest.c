#include <stdio.h>

typedef long T;
#include "OrderedSet.h"

OrderedSet* multiples(long number, long start, long end)
{
	long i;

	OrderedSet* set = createOrderedSet(end - start + 1);

	if(start % number != 0)
		start = (start / number) * number + number;

	for(i = start; i <= end; i += number)
		add(set, i);

	return set;
}

void printOrderedLongSet(OrderedSet* set)
{
	long i;

	printf("There are %ld elements: ", set -> size);

	for(i = 0; i < set -> size; i++)
		printf("%ld ", set -> elements[i]);

	printf("\n");
}

int main()
{
	OrderedSet *s1, *s2, *sU, *sI;

	s1 = multiples(3, 0, 25);
	printOrderedLongSet(s1);

	s2 = multiples(4, 0, 30);
	printOrderedLongSet(s2);

	sU = unionOrderedSets(s1, s2);
	printf("reunion: ");
	printOrderedLongSet(sU);

	sI = intersectOrderedSets(s1, s2);
	printf("intersection: ");
	printOrderedLongSet(sI);


	return 0;
}