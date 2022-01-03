#ifndef TREE_H_D
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct node
  {
    Item  elem;
    struct node *lt;
    struct node *rt;
  } TreeNode, *TTree;

void Init(TTree *t, Item x)
{
	// aloc memorie pentru un nod
	TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));

	(*t) = node;

	(*t) -> elem = x;
	(*t) -> lt = NULL;
	(*t) -> rt = NULL;
}

void Insert(TTree *t, Item x)
{
	if((*t) == NULL)
	{
		Init(t, x);
	}
	else
	{
		TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));

		if(!node)
			return;

		node -> elem = x;
		node -> lt = NULL;
		node -> rt = NULL;

		TreeNode* tree = *t;
		TreeNode* pred = NULL;

		while(tree)
		{
			pred = tree;

			if(x < tree -> elem)
				tree = tree -> lt;
			else
				tree = tree -> rt;
		}
		
		if(x < pred -> elem)
			pred -> lt = node;
		else
			pred -> rt = node;
	}
}

void PrintPostorder(TTree t)
{
	if(!t)
		return;

	PrintPostorder(t -> lt);
	PrintPostorder(t -> rt);
	printf("%d ", t -> elem);
}

void PrintPreorder(TTree t)
{
	if(!t)
		return;

	printf("%d ", t -> elem);
	PrintPreorder(t -> lt);
	PrintPreorder(t -> rt);
}

void PrintInorder(TTree t)
{
	if(!t)
		return;

	PrintInorder(t -> lt);
	printf("%d ", t -> elem);
	PrintInorder(t -> rt);
}

void Free(TTree *t)
{
	if((*t) == NULL)
		return;

	Free(&((*t) -> lt));
	Free(&((*t) -> rt));

	free(*t);
}

int Size(TTree t)
{
	if(!t)
		return 0;

	return 1 + Size(t -> lt) + Size(t -> rt);
}

int maxim(int x, int y)
{
	if(x > y)
		return x;

	return y;
}


int maxDepth(TTree t)
{
	if(t)
	{
		if(t -> lt == NULL && t -> rt == NULL)
			return 0;

		return 1 + maxim(maxDepth(t -> lt), maxDepth(t -> rt));
	}
}


int NoLeaves (TTree t)
{
    if(!t)
    	return 0;

    if(t -> lt == NULL && t -> rt == NULL)
    	return 1 + NoLeaves(t -> lt) + NoLeaves(t -> rt);
    
    return NoLeaves(t -> lt) + NoLeaves(t -> rt);
}

TTree Where (TTree t, Item x)
{
	if(!t)
		return NULL;

	while(t -> elem != x)
	{
		if(x < t -> elem)
			t = t -> lt;
		else
			t = t -> rt;
	}

	return t;
}


#endif // LINKEDSTACK_H_INCLUDED


