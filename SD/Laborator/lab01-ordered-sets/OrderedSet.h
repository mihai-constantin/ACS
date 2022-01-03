#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
  T* elements;                    // pointer to where the elements are in memory
  long size;                                // the number of elements in the set
  long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

  OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

  newSet->size = 0;                        // initially, the set is empty
  newSet->capacity = initialCapacity;
  newSet->elements = (T*) malloc(initialCapacity * sizeof(T));

  return newSet;
}

// -----------------------------------------------------------------------------

/*
  Function that checks if an element exists in a given set. As the
  elements of the set are ordered in memory, this function uses binary
  search.

  Function returns 1 if the given element exists in the set, and 0
  otherwise.
*/

int contains(OrderedSet* set, const T element) {
	
	long st, dr, mid;
    
	if(!set)
		return 0;

	st = 0;
	dr = set -> size - 1;

	while(st <= dr)
	{
		mid = st + (dr - st) / 2;

		if(set -> elements[mid] == element)
			return 1;

		if(set -> elements[mid] < element)
			st = mid + 1;
		else
			dr = mid - 1;
	}

  	return 0;
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/

int cmp(const void *a, const void *b)
{
	T* e1 = (T*) a;
	T* e2 = (T*) b;

	return *e1 - *e2;
}

void add(OrderedSet* set, const T newElement) {

	if(!set)
		return;

	// verific daca mai este loc pentru a adauga un element 
	if(set -> capacity == set -> size)
	{
		set = (OrderedSet*)realloc(set, (2 * set -> capacity) * sizeof(OrderedSet));

		if(!set)
			return;
	}

	// verific daca elementul pe care vreau sa il adaug nu este deja in set
	int gasit = contains(set, newElement);

	if(!gasit)
	{
		//adaug noul element in set
		set -> size++;
		set -> elements[set -> size - 1] = newElement;
	}

	qsort(set -> elements, set -> size, sizeof(T), cmp);
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the union of
  the two
*/

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
    
	int i;

	if(!s1 || !s2)
		return NULL;

	OrderedSet* s3 = createOrderedSet(s1 -> capacity + s2 -> capacity);

	if(!s3)
		return NULL;

	//copiez s1 in s3
	s3 -> size = s1 -> size;

	for(i = 0; i < s1 -> size; i++)
		s3 -> elements[i] = s1 -> elements[i];

	for(i = 0; i < s2 -> size; i++)
	{
		int gasit = contains(s3, s2 -> elements[i]);

		if(!gasit)
			add(s3, s2 -> elements[i]);
	}

  	return s3;
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

long minim(long x, long y)
{
	if(x < y)
		return x;

	return y;
}

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {
	
  	if(!s1 || !s2)
  		return NULL;

  	OrderedSet* s3 = createOrderedSet(minim(s1 -> capacity, s2 -> capacity));

  	if(!s3)
  		return NULL;
 
  	//parcurg setul cu set -> size minim
  	int i;

  	if(s1 -> size < s2 -> size)
  	{	
  		for(i = 0; i < s1 -> size; i++)
  		{
  			int gasit = contains(s2, s1 -> elements[i]);

  			if(gasit)
  				add(s3, s1 -> elements[i]);
  		}
  	}
  	else
  	{
  		for(i = 0; i < s2 -> size; i++)
  		{
  			int gasit = contains(s1, s2 -> elements[i]);

  			if(gasit)
  				add(s3, s2 -> elements[i]);
  		}
  	}

  	return s3;
}


// -----------------------------------------------------------------------------

#endif
