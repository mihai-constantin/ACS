#ifndef BST_H_
#define BST_H_

#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just assume
  some type T was previously defined.
 */

// -----------------------------------------------------------------------------

/*
 * !!!!ATENTION!!!!
 * 1. This implementation uses two sentinels (dummy nodes) root and nil.
 * 2. The convetion is that we always root the tree at root->l (the left of the root sentinel)
 */

typedef struct BSTNode{
	Item elem;
	struct BSTNode *p; // parent - not really needed, but simplifies implementation.
	struct BSTNode *l; // left child.
	struct BSTNode *r; // right child.
}BSTNode;

typedef struct BSTree{
	long size; // This inintially is 0, and is updated by insert/delete
	BSTNode *root; // The sentinel root (a sentinel not the actual root). The actual root node is root->l !
	BSTNode *nil; // The nil sentinel to avoid checks for NULL
}BSTree;

// TODO: Cerinta 1 si 2

/*
 * IMPLEMENTATION ORDER:
 * 1.  createTree
 * 2.  isEmpty
 * 3.  insert
 * 4.  search
 * 5.  minimum
 * 6.  maximum
 * 7.  successor 
 * 8.  predecessor
 * 9.  destroyTree
 */

BSTree* createTree()
{
    BSTree* tree = (BSTree*) malloc(sizeof(BSTree));
    if(!tree)
        return NULL;
    
    tree -> root = (BSTNode*) malloc(sizeof(BSTNode));
    if(!tree -> root)
        return NULL;
    
    tree -> nil  = (BSTNode*) malloc(sizeof(BSTNode));
    if(!tree -> nil)
        return NULL;
    
    tree -> size = 0;
    
    tree -> root -> l = tree -> nil;
    tree -> root -> r = tree -> nil;
    tree -> root -> p = tree -> nil;
    
    tree -> nil -> l = tree -> nil;
    tree -> nil -> r = tree -> nil;
    tree -> nil -> p = tree -> nil;
    
    return tree;
}

int isEmpty(BSTree* tree)
{
    if(!tree)
        return 1;
    
    if(tree -> root -> l == tree -> nil)
        return 1;
    
    return 0;
}

int contains(BSTree* tree, Item elem)
{
    if(tree -> root -> l == tree -> nil) // arbore vid
        return 0;
    
    BSTNode* node = tree -> root -> l;
    
    while(node != tree -> nil)
    {
        if(elem == node -> elem)
            return 1;
        
        if(elem < node -> elem)
            node = node -> l;
        else
            if(elem > node -> elem)
                node = node -> r;
    }
    
    return 0;
}

void insert(BSTree* tree, Item elem)
{
    if(contains(tree, elem))
        return;
    
    // aloc memorie pentru nod
    BSTNode* node = (BSTNode*) malloc(sizeof(BSTNode));
    
    if(!node)
        return;
    
    node -> elem = elem;
    node -> p = tree -> nil;
    node -> l = tree -> nil;
    node -> r = tree -> nil;
    
    if(tree -> root -> l == tree -> nil) // arbore vid
    {
        node -> p = tree -> root;
        tree -> root -> l = node;
        tree -> size = 1;
    }
    else
    {
        BSTNode* iterator = tree -> root -> l;
        BSTNode* pred = iterator -> p;
        
        while(iterator != tree -> nil)
        {
            pred = iterator;
            
            if(elem < iterator -> elem)
                iterator = iterator -> l;
            else
                if(elem > iterator -> elem)
                    iterator = iterator -> r;
        }
        
        if(elem < pred -> elem)
        {
            pred -> l = node;
            node -> p = pred;
        }
        
        if(elem > pred -> elem)
        {
            pred -> r = node;
            node -> p = pred;
        }
        
        tree -> size += 1;
    }
}

BSTNode* search(BSTree* tree, Item elem)
{
    if(tree -> root -> l == tree -> nil) // arbore vid
        return NULL;
    
    BSTNode* iterator = tree -> root -> l;
    
    while(iterator != tree -> nil)
    {
        if(iterator -> elem == elem)
            return iterator;
        
        if(elem < iterator -> elem)
            iterator = iterator -> l;
        else
            if(elem > iterator -> elem)
                iterator = iterator -> r;
    }
    
    return NULL;
}

BSTNode* minimum(BSTree* tree, BSTNode* node)
{
    if(tree -> root -> l == tree -> nil) // arbore vid
        return NULL;
    
    BSTNode* iterator = node;
    BSTNode* pred = NULL;
    
    while(iterator != tree -> nil)
    {
        pred = iterator;
        iterator = iterator -> l;
    }
    
    return pred;
}

BSTNode* maximum(BSTree* tree, BSTNode* node)
{
    if(tree -> root -> l == tree -> nil) // arbore vid
        return NULL;
    
    BSTNode* iterator = node;
    BSTNode* pred = tree -> nil;
    
    while (iterator != tree -> nil)
    {
        pred = iterator;
        iterator = iterator -> r;
    }
    
    return pred;
}

BSTNode* successor(BSTree* tree, BSTNode* node)
{
    if(node -> r != tree -> nil)
    {
        // exista subarbore drept
        return minimum(tree, node -> r);
    }
    else
    {
        while(node -> p -> l != node)
        {
            node = node -> p;
        }
        
        // nodul cu cea mai mare valoare din arbore nu are succesor
        if(node -> p == tree -> root)
            return NULL;
        
        return node -> p;
    }
}

BSTNode* predecessor(BSTree* tree, BSTNode* node)
{
    if(node -> l != tree -> nil)
    {
        // exista subarborele stang
        return maximum(tree, node -> l);
    }
    else
    {
        while(node -> p -> r != node)
        {
            node = node -> p;
        }
        
        // nodul cu cea mai mica valoare din arbore nu are predecesor
        if(node -> p == tree -> nil)
            return NULL;
        
        return node -> p;
    }
}

void deleteTree(BSTree* tree, BSTNode* node)
{
    if(node == tree -> nil)
        return;
    
    deleteTree(tree, node -> l);
    deleteTree(tree, node -> r);
    free(node);
}

void destroyTree(BSTree* tree)
{
    if(!tree)
        return;
    
    deleteTree(tree, tree -> root -> l);
    
    free(tree -> root);
    free(tree -> nil);
    free(tree);
}

void delete(BSTree* tree, Item elem){
	BSTNode* z; // node to be deleted
	BSTNode* y; // Node that is spliced out
	BSTNode* x; // The child of the sliced out node

	// Needed to maintain a similar interface as in the previous labs
	if( (z = search(tree,elem)) == tree->nil)
		return;

	/*
	 * Note:
	 * Case 1: The node has no children
	 * Case 2: The node has one child
	 * Case 3: The node has two children
	 */

	// Are we in cases 1,2 or in case 3
	y = ( (z->l == tree->nil) || (z->r == tree->nil) ) ? z : successor(tree, z);

	// Set x to the child of y
	x = (y->l == tree->nil) ? y->r : y->l;

	/*
	 * Note:
	 * There is no need to check if x is a valid pointer, we have the sentinels!
	 */
	if (tree->root == (x->p = y->p)) // assignment of y->p to x->p is intentional
		tree->root->l = x;
	else if (y == y->p->l)
		y->p->l = x;
	else
		y->p->r = x;

	if (y != z){

		/*
		 * Note:
		 * The data type T might be a very big structure, thus copying the key
		 * from one node to another might be very inefficient. It is better to
		 * modify the actual links.
		 */

		//  y is the node to splice out and x is its child
		y->l = z->l;
		y->r = z->r;
		y->p = z->p;
		z->l->p = z->r->p = y;
		if (z == z->p->l) z->p->l = y;
		else z->p->r = y;
		free(z);
	} else {
		free(y);
	}

	tree->size--;
}

#endif /* BST_H_ */

