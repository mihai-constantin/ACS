// CONSTANTIN MIHAI - 311CD

#define _GNU_SOURCE
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stdlib.h>

#define MAX(a, b) (((a) >= (b))?(a):(b))
#define HEIGHT(x) ((x)?((x)->height):(0))

/*
  IMPORTANT!
  As we stick to pure C, we cannot use templates. We will just assume
  some type Item was previously defined.
 */
// -----------------------------------------------------------------------------

typedef struct node{
	void* elem;
	void* info;
	struct node *pt;
	struct node *lt;
	struct node *rt;
	struct node* next;
	struct node* prev;
	struct node* end;
	long height;
    int number; // camp adaugat -> indica cate elemente am intr-o lista dublu inlantuita
}TreeNode;

typedef struct TTree{
	TreeNode *root;
	void* (*createElement)(void*);
	void (*destroyElement)(void*);
	void* (*createInfo)(void*);
	void (*destroyInfo)(void*);
	int (*compare)(void*, void*);
	long size;
}TTree;


TTree* createTree(void* (*createElement)(void*), void (*destroyElement)(void*),
		void* (*createInfo)(void*), void (*destroyInfo)(void*),
		int compare(void*, void*)){
	/* 1. This tree does NOT have any sentinels!!!
	 * "root" is just a pointer to the actual root node.
	 * 2. You must set all function pointers in the structure!!!
	 */
    
    TTree* newTree = (TTree*) malloc(sizeof(TTree));
    
    if(!newTree)
        return NULL;
    
    newTree -> root = NULL;
    
    // setez toate functiile in structura
    newTree -> createElement = createElement;
    newTree -> destroyElement = destroyElement;
    newTree -> createInfo = createInfo;
    newTree -> destroyInfo = destroyInfo;
    newTree -> compare = compare;
    
    newTree -> size = 0;
    
    return newTree;
}

TreeNode* createTreeNode(TTree *tree, void* value, void* info){
	/* Implementing and using this function
	 * will greatly improve your chances of 
	 * getting this to work.
	 */
    
    TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
    
    if(!newNode)
        return NULL;
    
    newNode -> lt = newNode -> rt = newNode -> pt = NULL;
    
    newNode -> next = NULL;
    newNode -> prev = NULL;
    newNode -> end = newNode;
    
    newNode -> elem = tree -> createElement(value);
    newNode -> info = tree -> createInfo(info);
    newNode -> height = 1;
    
    return newNode;
}

void destroyTreeNode(TTree *tree, TreeNode* node){
    
    if(!node || !tree)
        return;
    
    if((node -> elem) != NULL)
        free(node -> elem);
    
    if((node -> info) != NULL)
        free(node -> info);
    
    free(node);
    node = NULL;
}

void avlDestroyTreeHelper(TTree* tree, TreeNode* node)
{
    if(node == NULL)
        return;
    
    avlDestroyTreeHelper(tree, node -> lt);
    avlDestroyTreeHelper(tree, node -> rt);
    destroyTreeNode(tree, node);
}

void destroyTree(TTree* tree){
    /* What is the easiest way to get rid of all elements for this SPECIAL tree? */
    
    if(tree == NULL)
        return;
    
    avlDestroyTreeHelper(tree, tree -> root);
    
    free(tree);
    tree = NULL;
}

/*
void PreOrder(TTree* tree, TreeNode* node)
{
    if(node == NULL)
        return;
    
    PreOrder(tree, node -> lt);
    printf("%s -> %d\n", ((char*)(node -> elem)), *(int*)(node -> info));
    PreOrder(tree, node -> rt);
}
*/

int isEmpty(TTree* tree){
    
    if(!tree)
        return 1;
    
    if(!tree -> root)
        return 1;
    
    return 0;
}

TreeNode* search(TTree* tree, TreeNode* x, void* elem){
    
    if(isEmpty(tree))
        return NULL;
    
    TreeNode* iterator = x;
    
    while(iterator != NULL)
    {
        if((tree -> compare)((void*)(iterator -> elem), (void*)(elem)) == 0)
            return iterator;
        
        if((tree -> compare)((void*)(iterator -> elem), (void*)(elem)) == 1)
            iterator = iterator -> lt;
        else
            if((tree -> compare)((void*)(iterator -> elem), (void*)(elem)) == -1)
                iterator = iterator -> rt;
    }
    
    return NULL;
}

TreeNode* minimum(TTree*tree, TreeNode* x){
	
    if(isEmpty(tree))
        return NULL;
    
    while(x -> lt != NULL)
        x = x -> lt;
    
    return x;
}

TreeNode* maximum(TTree* tree, TreeNode* x){
	
	if(isEmpty(tree))
        return NULL;
    
    while(x -> rt != NULL)
        x = x -> rt;
    
    return x;
}

TreeNode* successor(TTree* tree, TreeNode* x){
    
    if(x -> rt != NULL)
    {
        // exista subarbore drept
        return minimum(tree, x -> rt);
    }
    else
    {
        if(x -> pt == NULL)
            return NULL;
        
        while(x -> pt -> lt != x)
        {
            x = x -> pt;
            
            // nodul cu cea mai mare valoare din arbore nu are succesor
            if(x -> pt == NULL)
                return NULL;
        }
        
        return x -> pt;
    }
}

TreeNode* predecessor(TTree* tree, TreeNode* x){
	
	if(x -> lt != NULL)
    {
        // exista subarbore stang
        return maximum(tree, x -> lt);
    }
    else
    {
        if(x -> pt == NULL)
            return NULL;
        
        while(x -> pt -> rt != x)
        {
            x = x -> pt;
            
            // nodul cu cea mai mica valoare din arbore nu are predecesor
            if(x -> pt == NULL)
                return NULL;
        }
        
        return x -> pt;
    }
}

void avlRotateLeft(TTree* tree, TreeNode* x){
	/* You may want to use the macros at the top of this file. */
    
    if(isEmpty(tree))
        return;
    
    TreeNode* parent = x -> pt;
    
    // verific daca exista subarbore drept
    if(x -> rt != NULL)
    {
        TreeNode* y = x -> rt;
        TreeNode* y_left = y -> lt;
        TreeNode* y_right = y -> rt;
        
        y -> pt = parent; // parintele lui y devine parintele lui x
        
        if(x == tree -> root)
            tree -> root = y; // y devine radacina arborelui
        else
        {
            if((tree -> compare)(parent -> elem, y -> elem) == 1)
                parent -> lt = y; // y devine fiu stanga
            else
                if((tree -> compare)(parent -> elem, y -> elem) == -1)
                    parent -> rt = y; // y devine fiu dreapta
        }
        
        x -> pt = y; // parintele lui x devine y
        y -> lt = x; // x devine fiu stanga pentru y
        
        x -> rt = y_left;
        
        if(y_left != NULL)
            y_left -> pt = x; // parintele subarborelui stang al lui y devine x
        
        // actualizare inaltimi
        x -> height = 1 + MAX(HEIGHT(x -> lt), HEIGHT(x -> rt));
        y -> height = 1 + MAX(HEIGHT(y -> lt), HEIGHT(y -> rt));
    }
}

void avlRotateRight(TTree* tree, TreeNode* y){
	/* You may want to use the macros at the top of this file. */
    
    if(isEmpty(tree))
        return;
    
    TreeNode* parent = y -> pt;
    
    // verific daca exista subarbore stang
    if(y -> lt != NULL)
    {
        TreeNode* x = y -> lt;
        TreeNode* x_left = x -> lt;
        TreeNode* x_right = x -> rt;
        
        x -> pt = parent; // parintele lui x devine parintele lui y
        
        if(y == tree -> root)
            tree -> root = x; // x devine radacina arborelui
        else
        {
            if((tree -> compare)(parent -> elem, x -> elem) == 1)
                parent -> lt = x; // x devine fiu stanga
            else
                if((tree -> compare)(parent -> elem, x -> elem) == -1)
                    parent -> rt = x; // x devine fiu dreapta
        }
        
        x -> rt = y; // y devine fiu dreapta pentru x
        y -> pt = x; // parintele lui y devine x
        
        y -> lt = x_right;
        
        if(x_right != NULL)
            x_right -> pt = y; // parintele subarborelui drept al lui x devine y
        
        // actualizare inaltimi
        y -> height = 1 + MAX(HEIGHT(y -> lt), HEIGHT(y -> rt));
        x -> height = 1 + MAX(HEIGHT(x -> lt), HEIGHT(x -> rt));
    }
}

int avlGetBalance(TTree* tree, TreeNode *x){
	/* Get AVL balance factor for node x.
	 * You may want to use the macros at the top of this file.
     */
    
    if(x == NULL)
        return 0;
    
    // use the macros at the top of this file
    return HEIGHT(x -> lt) - HEIGHT(x -> rt);
}

void avlFixUp(TTree* tree, TreeNode* node){
	/* Fix any unblance from this node to the top of tree */
    
    // Reechilibrarea arborelui
    TreeNode* key = node;
    
    // caut primul nod care nu este echilibrat
    while(node != NULL)
    {
        if(abs(avlGetBalance(tree, node)) > 1)
        {
            // am gasit nodul -> vad in ce caz sunt
            
            // cazul stanga - stanga -> rotatie dreapta
            if(avlGetBalance(tree, node) > 1 && (tree -> compare)(key -> elem, node -> lt -> elem) == -1)
            {
                avlRotateRight(tree, node);
            }
            else
                // cazul dreapta - dreapta -> rotatie stanga
                if(avlGetBalance(tree, node) < -1 && (tree -> compare)(key -> elem, node -> rt -> elem) == 1)
                {
                    avlRotateLeft(tree, node);
                }
                else
                    // cazul stanga - dreapta
                    if(avlGetBalance(tree, node) > 1 && (tree -> compare)(key -> elem, node -> lt -> elem) == 1)
                    {
                        avlRotateLeft(tree, node -> lt);
                        avlRotateRight(tree, node);
                    }
                    else
                        // cazul dreapta - stanga
                        if(avlGetBalance(tree, node) < -1 && (tree -> compare)(key -> elem, node -> rt -> elem) == -1)
                        {
                            avlRotateRight(tree, node -> rt);
                            avlRotateLeft(tree, node);
                        }
            
            // parcurg parintii nodului adaugat
            while(key != NULL)
            {
                key -> height = 1 + MAX(HEIGHT(key -> lt), HEIGHT(key -> rt));
                key = key -> pt;
            }
            
            break;
        }
        
        node = node -> pt;
    }
}

void avlFixUp2(TTree* tree, TreeNode* node){
    
    // caut primul nod care nu este echilibrat
    while(node != NULL)
    {
        if(abs(avlGetBalance(tree, node)) > 1)
        {
            // am gasit nodul -> vad in ce caz sunt
            
            // cazul stanga - stanga -> rotatie dreapta
            if(avlGetBalance(tree, node) > 1)
            {
                TreeNode* key = node -> lt;
                
                if(key -> lt != NULL)
                {
                    avlRotateRight(tree, node);
                }
                else
                    if(key -> rt != NULL)
                    {
                        avlRotateLeft(tree, node -> lt);
                        avlRotateRight(tree, node);
                    }
            }
            else
            {
                if(avlGetBalance(tree, node) < -1)
                {
                    TreeNode* key = node -> rt;
                    
                    if(key -> rt != NULL)
                    {
                        // cazul dreapta - dreapta -> rotatie stanga
                        avlRotateLeft(tree, node);
                    }
                    else
                        if(key -> lt != NULL)
                        {
                            // cazul dreapta - stanga
                            avlRotateRight(tree, node -> rt);
                            avlRotateLeft(tree, node);
                        }
                }
            }
            
            // parcurg parintii nodului adaugat
            TreeNode* key = minimum(tree, tree -> root);
            
            while(key != NULL)
            {
                key -> height = 1 + MAX(HEIGHT(key -> lt), HEIGHT(key -> rt));
                key = key -> pt;
            }
            
            break;
        }
        
        node = node -> pt;
    }
}

void insert(TTree* tree, void* elem, void* info) {
	/*
	 * 1. Begin by implementing the normal BST insersion (no duplicates).
	 * 2. Fix any unbalance caused by this insertion as the last operation.
	 * 3. Now if this element is a duplicate all you have to do is to
	 *    inserted in the approapiate list. Inseting the duplicate at the
	 *    end of a list is easier and consistent!
	 */
    
    // aloc memorie pentru un nod
    TreeNode* node = createTreeNode(tree, (void*)elem, (void*)info);
    TreeNode* key = NULL;
    
    if((key = search(tree, tree -> root, (void*)(node -> elem))) != NULL)
    {
        // formez legaturile din lista dublu inlantuita alcatuita din elementele duplicate
        
        key -> number++;
        
        key -> end -> next = node;
        node -> prev = key -> end;
        key -> end = node;
        
        node -> next = successor(tree, key);
        
        if(node -> next != NULL)
            successor(tree, key) -> prev = key -> end;
        
        return;
    }
    
    if(isEmpty(tree))  // arbore vid
    {
        node -> pt = NULL;
        tree -> root = node;
        tree -> size = 1;
        node -> number = 1;
    }
    else
    {
        TreeNode* iterator = tree -> root;
        TreeNode* pred = NULL;
        
        while(iterator != NULL)
        {
            pred = iterator;
            
            if((tree -> compare)((void*)(node -> elem), (void*)(iterator -> elem)) == -1)
                iterator = iterator -> lt;
            else
                if((tree -> compare)((void*)(node -> elem), (void*)(iterator -> elem)) == 1)
                    iterator = iterator -> rt;
        }
        
        if((tree -> compare)((void*)(node -> elem), (void*)(pred -> elem)) == -1)
        {
            pred -> lt = node;
            node -> pt = pred;
            node -> number = 1;
            
            // actualizare next si prev
            pred -> end -> prev = node;
            node -> end -> next = successor(tree, node);
            
            // parcurg parintii nodului adaugat
            while(pred != NULL)
            {
                long h1 = 0, h2 = 0;
                
                if(pred -> lt != NULL)
                    h1 = pred -> lt -> height;
                
                if(pred -> rt != NULL)
                    h2 = pred -> rt -> height;
                
                pred -> height = 1 + MAX(h1, h2);
                pred = pred -> pt;
            }
        }
        else
            if((tree -> compare)((void*)(node -> elem), (void*)(pred -> elem)) == 1)
            {
                pred -> rt = node;
                node -> pt = pred;
                node -> number = 1;
                
                // actualizare next si prev
                pred -> end -> next = node;
                node -> end -> prev = pred;
                
                // parcurg parintii nodului adaugat
                while(pred != NULL)
                {
                    long h1 = 0, h2 = 0;
                    
                    if(pred -> lt != NULL)
                        h1 = pred -> lt -> height;
                    
                    if(pred -> rt != NULL)
                        h2 = pred -> rt -> height;
                    
                    pred -> height = 1 + MAX(h1, h2);
                    pred = pred -> pt;
                }
            }
        
        tree -> size += 1;
        
        avlFixUp(tree, node);
    }
}

void delete(TTree* tree, void* elem){
	/*
	 * 1. Begin by implementing the normal BST deletion (no duplicates).
	 * 2. Fix any unbalance caused by this insertion as the last operation.
	 * 3. Now what happends if the elem you are trining to delete has duplicates?
	 *    Is it easier to delete the duplicate? Which one?
	 *    What happends to the tree-list when you delete an elem with no duplicates?
	 *    
	 */
    
    TreeNode* key = search(tree, tree -> root, elem);  // caut nodul in AVL
    
    if(key == NULL)
        return;
    
    if(tree -> size == 1){
        
        tree -> size = 0;
        TreeNode *aux = tree -> root;
        destroyTreeNode(tree, aux);
        tree -> root = NULL;
        return;
    }
    
    // vad daca elementul are duplicate
    if(key -> end != key)
    {
        // sterg ultimul duplicat din lista aferenta nodului
        TreeNode* aux = key -> end;
        key -> end = key -> end -> prev;
        key -> end -> next = successor(tree, key);
        
        if(key -> end -> next != NULL)
            successor(tree, key) -> prev = key -> end;
            
        destroyTreeNode(tree, aux);
        return;
    }
    
    // element unic in AVL
    
    /*
        verific in ce caz sunt
        1. nod frunza
        2. nod cu un copil
        3. nod cu 2 copii
    */
    
    if(key -> height == 1)  // key e nod frunza
    {
        TreeNode* parent = key -> pt;
        TreeNode* node = parent;
        
        if(parent == NULL) // arborele devine vid
        {
            TreeNode* aux = tree -> root;
            tree -> size = 0;
            
            destroyTreeNode(tree, aux);
            tree -> root = NULL;
            return;
        }
        else
        {
            if((tree -> compare)(key -> elem, parent -> elem) == -1)
            {
                parent -> lt = NULL;
                parent -> prev = predecessor(tree, parent);
            }
            else
                if((tree -> compare)(key -> elem, parent -> elem) == 1)
                {
                    parent -> rt = NULL;
                    parent -> next = successor(tree, parent);
                }
        }
            
        TreeNode* key2 = minimum(tree, tree -> root);
            
        while(key2 != NULL)
        {
            key2 -> height = 1 + MAX(HEIGHT(key2 -> lt), HEIGHT(key2 -> rt));
            key2 = key2 -> pt;
        }
            
        avlFixUp2(tree, parent);
        
        tree -> size--;
        
        destroyTreeNode(tree, key);
    }
    else
    {
        // verific daca sunt in cazul 2 sau 3
        if(key -> lt != NULL && key -> rt != NULL)
        {
            // cazul 3 : nodul key are 2 copii
            TreeNode* aux = successor(tree, key);
            TreeNode* Aux = NULL;
            
            key -> elem = (void*)(aux -> elem);
            key -> info = (void*)(aux -> info);
            
            key -> next = aux -> next; // se modifica si legaturile din lista
            
            TreeNode* parent = aux -> pt;
            //TreeNode* fiu_lt = aux -> lt;
            TreeNode* fiu_rt = aux -> rt;
            
            if((tree -> compare)(aux -> elem, parent -> elem) == -1)
            {
                parent -> lt = fiu_rt;
                //destroyTreeNode(tree, aux);
                free(aux);
                aux = NULL;
            }
            else
                parent -> rt = NULL;
                
            // reechilibrare
            TreeNode* key2 = minimum(tree, tree -> root);
            while(key2 != NULL)
            {
                key2 -> height = 1 + MAX(HEIGHT(key2 -> lt), HEIGHT(key2 -> rt));
                key2 = key2 -> pt;
            }
            
            key2 = maximum(tree, tree -> root);
            while(key2 != NULL)
            {
                key2 -> height = 1 + MAX(HEIGHT(key2 -> lt), HEIGHT(key2 -> rt));
                key2 = key2 -> pt;
            }
                
            avlFixUp2(tree, parent);
            tree -> size--;
            
            if(aux)
                free(aux);
            
            //destroyTreeNode(tree, Aux);
        }
        else
        {
            // cazul 2 : nodul key are un singur copil
            if(key -> lt != NULL)
            {
                // nu stiu daca mai trebuie sa fac aici ceva. Oricum merge :)
            }
            else
                if(key -> rt != NULL)
                {
                    TreeNode* aux = key -> rt;
                    TreeNode* key_rt = aux;
                    
                    key -> elem = (void*)(aux -> elem);
                    key -> info = (void*)(aux -> info);
                    
                    TreeNode* aux2 = aux;
                    TreeNode* parent = aux -> pt;
                    
                    if((tree -> compare)(aux -> elem, parent -> elem) == -1)
                    {
                        destroyTreeNode(tree, key -> lt);
                        parent -> lt = NULL;
                    }
                    else
                        parent -> rt = NULL;
                            
                    tree -> size--;
                    
                    // parcurg parintii nodului adaugat
                    while(aux2 != NULL)
                    {
                        aux2 -> height = 1 + MAX(HEIGHT(aux2 -> lt), HEIGHT(aux2 -> rt));
                        aux2 = aux2 -> pt;
                    }
                    
                    avlFixUp(tree, aux);
                    
                    if(aux)
                        free(aux);
                    
                    aux = NULL;
                    
                    //destroyTreeNode(tree, key_rt);
                }
        }
    }
}

#endif /* AVLTREE_H_ */
