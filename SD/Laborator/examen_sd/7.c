#include <stdio.h>
#include <stdlib.h>

/* Diametrul unui arbore. Problema clasica. 2 BFS - uri */

typedef struct node{
    int elem;
    struct node* lt;
    struct node* rt;
}TNode;

typedef struct TTree{
    long size;
    TNode* root;
    TNode* nil;
}TTree;

TTree* createTree(){
    
    TTree* tree =(TTree*) malloc(sizeof(TTree));

    tree -> size = 0;
    
    /* aloc memorie pentru cele 2 noduri santinela */
    tree -> root = (TNode*) malloc(sizeof(TNode));
    tree -> nil = (TNode*) malloc(sizeof(TNode));
    
    tree -> root -> lt = tree -> root -> rt = tree -> nil;
    tree -> nil -> lt = tree -> root -> rt = tree -> nil;

    return tree;
}

/* inserare ca la BST */
void insert(TTree* tree, int elem){
    
    /* aloc memorie pentru un nod */
    TNode* node = (TNode*) malloc(sizeof(TNode));
    
    node -> elem = elem;
    node -> lt = node -> rt = tree -> nil;
    
    TNode* iterator = tree -> root -> lt;
    
    /* adaug radacina arborelui */
    if(iterator == tree -> nil){
        tree -> root -> lt = node;
    }
    else{
        /* caut locul unde trebuie sa introduc noul element */
        
        TNode* prev = NULL;
        
        while(iterator != tree -> nil){
    
            prev = iterator;
            if(iterator -> elem > elem)
                iterator = iterator -> lt;
            else
                iterator = iterator -> rt;
        }
        
        if(prev -> elem > elem)
            prev -> lt = node;
        else
            prev -> rt = node;
    }
    
    tree -> size++;
}

void printTree(TTree* tree, TNode* node){
    
    if(node == tree -> nil)
        return;
    
    printTree(tree, node -> lt);
    
   
    if(node -> elem % 2 == 0)
        printf("%d ", node -> elem);
    
    printTree(tree, node -> rt);
}

int main()
{
    int numberofNodes;
    scanf("%d", &numberofNodes);
    
    TTree* tree = createTree();
    
    for(int i = 0; i < numberofNodes; i++){
        int x;
        scanf("%d", &x);
        insert(tree, x);
        
        printf("=== PostOrder ===\n");
        printTree(tree, tree -> root -> lt);
        
        printf("\n");
    }
    
    printf("=== PostOrder ===\n");
    printTree(tree, tree -> root -> lt);
    
    printf("\n");
    
    return 0;
}
