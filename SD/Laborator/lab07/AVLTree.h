
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include<stdlib.h>

// An AVL tree node
typedef struct AVLNode{
	Item elem;
	int height;
	struct AVLNode *l;
	struct AVLNode *r;
	struct AVLNode *p;

}AVLNode;

typedef struct AVLTree{
	long size;
	AVLNode* root;
	AVLNode* nil;
	int (*comp)(Item a, Item b);
}AVLTree;

AVLTree* avlCreateTree(int (*comp)(Item a, Item b))
{
	AVLTree* newTree = (AVLTree*) malloc(sizeof(AVLTree));
	newTree->comp = comp;
    
	newTree->nil = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
	newTree->nil->height = 0;
    
	newTree->root = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->root->p = newTree->root->l = newTree->root->r = newTree->nil;
	newTree->root->height = 0;
    
	newTree->size = 0;

	return newTree;
}

int avlIsEmpty(AVLTree* tree){
	return (tree->root->l == tree->nil);
}

AVLNode* avlNewNode(AVLTree* tree){
	AVLNode* newNode = (AVLNode*) malloc(sizeof(AVLNode));
	// Initialize the new node to be used in the tree
	newNode->p = newNode->r = newNode->l = tree->nil;
	newNode->height = 1;

	return newNode;
}

// A utility function to get maximum of two integers
int max(int a, int b){
	return (a > b)? a : b;
}

void PreOrder(AVLTree* tree, AVLNode* node)
{
    if(node == tree -> nil)
        return;
    
    printf("%ld -> %d; ", (*(node -> elem)), node -> height);
    PreOrder(tree, node -> l);
    PreOrder(tree, node -> r);
}

// A utility function to right rotate subtree rooted with y
void avlRightRotate(AVLTree *tree,  AVLNode *y){
	
	if(avlIsEmpty(tree))
        return;
    
    AVLNode* parent = y -> p;
    
    // verific daca exista subarbore stang
    if(y -> l != tree -> nil)
    {
        AVLNode* x = y -> l;
        AVLNode* x_left = x -> l;
        AVLNode* x_right = x -> r;
        
        x -> p = parent; // parintele lui x devine parintele lui y
        
        if(parent == tree -> root)
            tree -> root -> l = x; // x devine fiu stanga pentru root, adica radacina AVL-ului
        else
        {
            if((*(parent -> elem)) > (*(x -> elem)))
                parent -> l = x; // x devine fiu stanga
            else
                if((*(parent -> elem)) < (*(x -> elem)))
                    parent -> r = x; // x devine fiu dreapta
        }
        
        x -> r = y; // y devine fiu dreapta pentru x
        y -> p = x; // parintele lui y devine x
        
        y -> l = x_right;
        x_right -> p = y;
        
        // actualizare inaltimi
        y -> height = 1 + max(y -> l -> height, y -> r -> height);
        x -> height = 1 + max(x -> l -> height, x -> r -> height);
    }
}

// A utility function to left rotate subtree rooted with x
void avlLeftRotate(AVLTree *tree, AVLNode *x){
	
	if(avlIsEmpty(tree))
        return;
    
    AVLNode* parent = x -> p;
    
    // verific daca exista subarbore drept
    if(x -> r != tree -> nil)
    {
        AVLNode* y = x -> r;
        AVLNode* y_left = y -> l;
        AVLNode* y_right = y -> r;
        
        y -> p = parent; // parintele lui y devine parintele lui x
        
        if(parent == tree -> root)
            tree -> root -> l = y; // y devine fiul stanga pentru root, adica radacina AVL-ului
        else
        {
            if((*(parent -> elem)) > (*(y -> elem)))
                parent -> l = y; // y devine fiu stanga
            else
                if((*(parent -> elem)) < (*(y -> elem)))
                    parent -> r = y; // y devine fiu dreapta
        }
        
        x -> p = y; // parintele lui x devine y
        y -> l = x; // x devine fiul stang al lui y
        
        x -> r = y_left;
        y_left -> p = x; // parintele subarborelui stang al lui y devine x
        
        // actualizare inaltimi
        x -> height = 1 + max(x -> l -> height, x -> r -> height);
        y -> height = 1 + max(y -> l -> height, y -> r -> height);
    }
}

// Get Balance factor of node x
int avlGetBalance(AVLNode *x){
	if (x == NULL)
		return 0;
	return x->l->height - x->r->height;
}

AVLNode * avlMinimum(AVLTree* tree, AVLNode* x){
	while (x->l != tree->nil)
		x = x->l;
	return x;
}

AVLNode* avlMaximum(AVLTree* tree, AVLNode* x){
	while(x->r != tree->nil){
		x = x->r;
	}
	return x;
}

int contains(AVLTree* tree, Item elem)
{
    if(avlIsEmpty(tree))
        return 0;
    
    AVLNode* iterator = tree -> root -> l;
    
    while(iterator != tree -> nil)
    {
         if((*(iterator -> elem)) == (*elem))
             return 1;
        
        if((*(iterator -> elem)) > (*elem))
            iterator = iterator -> l;
        else
            iterator = iterator -> r;
    }
    
    return 0;
}

void avlInsert(struct AVLTree* tree, Item elem){
	
	if(contains(tree, elem))
        return;
    
    // aloc memorie pentru nod
    AVLNode* node = avlNewNode(tree);
    node -> elem = elem;
    
    if(avlIsEmpty(tree)) // arbore vid
    {
        node -> p = tree -> root;
        tree -> root -> l = node;
        tree -> size = 1;
    }
    else
    {
        AVLNode* iterator = tree -> root -> l;
        AVLNode* pred = iterator -> p;
        
        while(iterator != tree -> nil)
        {
            pred = iterator;
            
            if((*elem) < (*(iterator -> elem)))
                iterator = iterator -> l;
            else
                if((*elem) > (*(iterator -> elem)))
                    iterator = iterator -> r;
        }
        
        if((*elem) < (*(pred -> elem)))
        {
            pred -> l = node;
            node -> p = pred;
            
            // parcurg parintii nodului adaugat
            while(pred != tree -> root)
            {
                pred -> height = 1 + max(pred -> l -> height, pred -> r -> height);
                pred = pred -> p;
            }
            
        }
        else
            if((*elem) > (*(pred -> elem)))
            {
                pred -> r = node;
                node -> p = pred;
            
                // parcurg parintii nodului adaugat
                while(pred != tree -> root)
                {
                    pred -> height = 1 + max(pred -> l -> height, pred -> r -> height);
                    pred = pred -> p;
                }
             
            }
        
        tree -> size += 1;
        
        // Reechilibrarea arborelui
        
        AVLNode* key = node; // nodul pe care l-am inserat
        
        // caut primul nod care nu este echilibrat
        while(node != tree -> root)
        {
            if(abs(avlGetBalance(node)) > 1)
            {
                /*
                printf("Initial configuration: ");
                PreOrder(tree, tree -> root -> l);
                printf("\n");
                 */
                
                // am gasit nodul -> vad in ce caz sunt
                
                // cazul stanga-stanga -> rotatie dreapta
                if(avlGetBalance(node) > 1 && (*(key -> elem)) < (*(node -> l -> elem)))
                {
                     avlRightRotate(tree, node);
                }
                else
                    // cazul dreapta-dreapta -> rotatie stanga
                    if(avlGetBalance(node) < -1 && (*(key -> elem)) > (*(node -> r -> elem)))
                    {
                        avlLeftRotate(tree, node);
                    }
                    else
                        // cazul stanga-dreapta
                        if(avlGetBalance(node) > 1 && (*(key -> elem)) > (*(node -> l -> elem)))
                        {
                            avlLeftRotate(tree, node -> l);
                            avlRightRotate(tree, node);
                            
                        }
                        else
                            // cazul dreapta-stanga
                            if(avlGetBalance(node) < -1 && (*(key -> elem)) < (*(node -> r -> elem)))
                            {
                                avlRightRotate(tree, node -> r);
                                avlLeftRotate(tree, node);
                            }
                
                // parcurg parintii nodului adaugat
                while(key != tree -> root)
                {
                    key -> height = 1 + max(key -> l -> height, key -> r -> height);
                    key = key -> p;
                }
                
                break;
            }
            
            node = node -> p;
        }
    }
}


void avlDeleteNode(AVLTree *tree, AVLNode* node){
	//destroyElem(node->elem);
    free(node -> elem);
	free(node);
}


void avlDestroyTreeHelper(AVLTree* tree, AVLNode* x) {
	if (x != tree->nil) {
		avlDestroyTreeHelper(tree,x->l);
		avlDestroyTreeHelper(tree,x->r);
		avlDeleteNode(tree,x);
	}
}

void avlDestroyTree(AVLTree* tree){
	avlDestroyTreeHelper(tree, tree->root->l);
	free(tree->root);
	free(tree->nil);
	free(tree);
}

#endif /* AVLTREE_H_ */
