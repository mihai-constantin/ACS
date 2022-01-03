#include <stdio.h>
#include <stdlib.h>

typedef int T;

typedef struct SortedList {
	T value;
	struct SortedList* next;
}SortedList;

SortedList* createList(long size)
{
	SortedList* list, *aux;

	list = (SortedList*) malloc(sizeof(SortedList));
	list -> value = 0;

	aux = list;

	for(int i = 1; i < size; i++)
	{
		aux -> next = (SortedList*) malloc(sizeof(SortedList));
		aux -> next -> value = i;

		aux = aux -> next;
	}

	aux -> next = list;

	return list;
}

SortedList* replace(SortedList* list, const T element, const T new_element)
{
	SortedList* aux = list;

	while(aux -> next != NULL && aux -> value != element)
		aux = aux -> next;

	if(aux -> value == element)
		aux -> value = new_element;

	return list;
}

SortedList* insert(SortedList* list, const T element)
{
	SortedList* node = (SortedList*) malloc(sizeof(SortedList));

	node -> value = element;
	node -> next = NULL;

	SortedList* aux = list;

	while(aux -> next != NULL && aux -> next -> value < element)
	{
		if(aux -> next -> value < element)
			aux = aux -> next;
	}

	node -> next = aux -> next;
	aux -> next = node;
	
	return list;
}

void write(SortedList* list)
{
	SortedList* aux;

	aux = list;

	while(list)
	{
		printf("%d ", list -> value);
		list = list -> next;

		if(list == aux)
			break;
	}

	printf("\n");
}

int main()
{
	/*SortedList* List;

	long size;
	//int element;
	scanf("%ld", &size);

	List = createList(size);
	write(List);
*/
	//List = insert(List, element);
	//write(List);

	char s[4] = "key4";

	int i, sum = 0;

	for(i = 0; i < 4; i++)
	{
		sum += s[i];
	}

	printf("%d\n", sum % 4);

	return 0;
}