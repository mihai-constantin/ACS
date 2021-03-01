/*
 * BSTList.c
 *
 *  Created on: Apr 2, 2016
 *      Author: dan
 */

typedef long Item;
#include "BST.h"
typedef BSTNode* Item2;
#include "List.h"
#include "Queue.h"


BSTree* buildTree(Item *array, long len);

// -----------------------------------------------------------------------------
List* bstToList(BSTree* tree){
    
    Queue* queue = NULL;
    initQueue(&queue); // initializare coada
    
    // adaug in coada nodul de start
    enqueue(queue, tree -> root -> l);
    
    List* list = createList(); // initializare lista
    listPushBack(list, tree -> root -> l);
    
    while(!isEmptyQueue(queue))
    {
        // extrag din coada primul nod
        BSTNode* node = front(queue);
        
        // adaug in coada vecinii nodului (left & right)
        if(node -> l != tree -> nil)
        {
            enqueue(queue, node -> l);
            listPushBack(list, node -> l);
        }
        
        if(node -> r != tree -> nil)
        {
            enqueue(queue, node -> r);
            listPushBack(list, node -> r);
        }
        
        dequeue(queue);
    }
    
    return list;
}

void printList(List* list){
    
    if(isEmptyList(list))
        return;
    
    ListNode* iterator = list -> head -> next;
    
    while(iterator != list -> head)
    {
        BSTNode* node = iterator -> elem;
        printf("%ld ", node -> elem);
        iterator = iterator -> next;
    }
    
    printf("\n");
}
// -----------------------------------------------------------------------------

int main(void){
	Item array[] = {5,3,2,4,7,6,8};

	BSTree *tree = buildTree(array, sizeof(array)/sizeof(Item));

	List *list = bstToList(tree);
	printList(list);

	destroyTree(tree);

	return 0;
}

BSTree* buildTree(Item *array, long len){
	BSTree* newTree = createTree();
	for(int i = 0; i < len; i++){
		insert(newTree,array[i]);
	}
	return newTree;
}
