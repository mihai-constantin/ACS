#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef struct SortedList {
  T value;
  struct SortedList* next;
} SortedList;

void init(SortedList** list)
{
	*list = NULL;
}

long isEmpty(SortedList* list)
{	
	if(!list)
		return 1l;

	return 0l;
}

long contains(SortedList* list, T element)
{	
	if(isEmpty(list))
		return 0l;

	while(list)
	{
		if(list -> value == element)
			return 1l;

		list = list -> next;
	}

	return 0l;
}

void insert(SortedList** list, T new_element)
{
	SortedList* List = *list;

	SortedList* node = (SortedList*) malloc(sizeof(SortedList));

	if(!node)
		return;

	node -> value = new_element;
	node -> next = NULL;

	SortedList* pred = NULL;

	if(isEmpty(List))
	{
		*list = node;
	}
	else
	{
		if(List -> value > new_element)
		{
			node -> next = List;
			*list = node;
		}
		else
		{
			while(List)
			{
				if(List -> value <= new_element)
				{
					pred = List;
					List = List -> next;
				}
				else
				{
					break;
				}
			}

			pred -> next = node;
			node -> next = List;
		}
	}
}

long length(SortedList* list)
{
	long lung = 0;

	if(isEmpty(list))
		return 0l;

	while(list)
	{
		lung++;
		list = list -> next;
	}

	return lung;
}

void deleteOnce(SortedList** list, T element)
{
	SortedList* List = *list;

	if(isEmpty(List))
		return;

	long gasit = contains(List, element);

	if(gasit)
	{
		if(List -> value == element)
		{
			SortedList* aux = *list;
			*list = (*list) -> next;
			free(aux);
		}
		else
		{
			SortedList* pred, *current;

			current = List;

			while(current && current -> value != element)
			{
				pred = current;
				current = current -> next;
			}

			pred -> next = current -> next;
			free(current);
		}
	}
}

T getNth(SortedList* list, long pos)
{
	if(!list)
		return 0;

	long lung = 1;

	while(list)
	{
		if(lung == pos)
			return list -> value;

		lung++;
		list = list -> next;
	}
	
	return 0;
}

void freeSortedList(SortedList** list)
{
	while(*list)
	{
		SortedList* aux = *list;
		*list = (*list) -> next;
		free(aux);
	}
}

#endif
