#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	ListNode* first; // link to the first node
	ListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createList(void){
	
	List* list = (List*) malloc(sizeof(List));
	
	if(!list)
		return NULL;
	
	list -> first = NULL;
	list -> last = NULL;

	return list;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmpty(List *list){
	
	if(!list || !list -> first)
		return 1;

	return 0;	
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int contains(List *list, Item elem){
	
	if(!list)
		return 0;

	ListNode* iterator = list -> first;

	if(!iterator)
		return 0;

	while(iterator)
	{
		if(iterator -> elem == elem)
			return 1;

		iterator = iterator -> next;
	}

	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */

void insertAt(List* list, Item elem, int pos){

	// Guard against young player errors
	if(!list) 
		return;

	if(pos == 0) // introducere element pe pozitia 0
	{
		ListNode* node = (ListNode*) malloc(sizeof(ListNode));

		if(!node)
			return;

		node -> elem = elem;
		node -> prev = NULL;
		node -> next = NULL;

		if(list -> first == NULL) // lista e goala
		{
			list -> first = node;
			list -> last = node;
		}
		else
		{
			list -> first -> prev = node;
			node -> next = list -> first;
			list -> first = node;
		}
	}
	else
		if(pos > 0)
		{
			ListNode* iterator = list -> first;
			ListNode* pred = NULL;

			int lung = 0;
			int gasit = 0;

			while(iterator)
			{
				if(lung == pos)
				{
					ListNode* node = (ListNode*) malloc(sizeof(ListNode));

					if(!node)
						return;

					node -> elem = elem;
					node -> prev = NULL;
					node -> next = NULL;

					node -> prev = pred;
					iterator -> prev -> next = node;
					iterator -> prev = node;
					node -> next = iterator;
					gasit = 1;
			
					break;
				}

				pred = iterator;

				lung++;
				iterator = iterator -> next;
			}

			if(lung == pos && !gasit) // inserez elementul la finalul listei
			{
				ListNode* node = (ListNode*) malloc(sizeof(ListNode));

				if(!node)
					return;

				node -> elem = elem;
				node -> prev = NULL;
				node -> next = NULL;

				pred -> next = node;
				node -> prev = list -> last;
				list -> last = node;
				gasit = 1;
			}
		}	
}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnce(List *list, Item elem) {
	// Guard against young player errors
	if(isEmpty(list)) 
		return;

	int gasit = contains(list, elem);

	if(gasit)
	{
		// elimin elementul din lista
		ListNode* iterator = list -> first;
		ListNode* pred = NULL;
		ListNode* aux;

		if(iterator -> elem == elem)
		{
			if(iterator -> next == NULL)
			{
				// lista devine vida
				aux = list -> first;
				list -> first = NULL;
				list -> last = NULL;
				free(aux);
			}
			else
			{
				aux = list -> first;
				iterator = iterator -> next;
				iterator -> prev = NULL;
				list -> first = iterator;
				free(aux);
			}
		}
		else
		{
			while(iterator)
			{
				if(iterator -> elem == elem)
				{
					aux = iterator;

					if(iterator -> next == NULL)
					{
						// elimin ultimul element din lista
						list -> last = pred;
						pred -> next = NULL;
						free(aux);
					}
					else
					{
						pred -> next = iterator -> next;
						iterator -> next -> prev = pred;
						free(aux);
					}

					break;
				}

				pred = iterator;
				iterator = iterator -> next;
			}
		}
	}


}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int length(List *list) {
	// Guard against young player errors
	if(!list || !list -> first) 
		return 0;

	// TODO: Cerinta 1f
	ListNode* iterator = list -> first;

	int lung = 0;

	while(iterator)
	{
		lung++;
		iterator = iterator -> next;
	}

	return lung;
}
// -----------------------------------------------------------------------------

/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
void destroyList(List* list){
	// Guard against young player errors
	if(!list) 
		return;

	//TODO: Cerinta 1g
	ListNode* iterator = list -> first;
	ListNode* aux;

	while(iterator)
	{
		aux = iterator;
		iterator = iterator -> next;	
		free(aux);
	}

	free(list);
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
