#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

void mirror(TTree *t) {

    if((*t) == NULL) // arbore vid
        return;

    if((*t) -> lt == NULL && (*t) -> rt == NULL) // nod frunza
        return;

    TreeNode* node = (TreeNode*) malloc(sizeof(TreeNode));

    if(!node)
        return;

    // swap 
    node = (*t) -> lt;
    (*t) -> lt = (*t) -> rt;
    (*t) -> rt = node;

    mirror(&((*t) -> lt));
    mirror(&((*t) -> rt));
}

int sameTree(TreeNode *t1, TreeNode *t2) {

    /* both empty -> true */
    if(!t1 && !t2)
        return 1;

    /* both non-empty -> compare them */
    if(t1 && t2)
        return  t1 -> elem == t2 -> elem && 
                sameTree(t1 -> lt, t2 -> lt) && sameTree(t1 -> rt, t2 -> rt);

    /* one empty, one not -> false */
    return 0;
}

int main()
{
    TTree t1=NULL, t2=NULL;
    Insert(&t1, 5); Insert(&t1, 3);
    Insert(&t1, 2); Insert(&t1, 4);
    Insert(&t1, 7); Insert(&t1, 6);
    Insert(&t1, 8);


    Insert(&t2, 5); Insert(&t2, 3);
    Insert(&t2, 2); Insert(&t2, 4);
    Insert(&t2, 9); Insert(&t2, 6);
    Insert(&t2, 8);

    printf("Preorder should be: 5 3 2 4 7 6 8 \nPreorder = ");
    PrintPreorder(t1);
    printf("\n\n");

    printf("Inorder should be: 2 3 4 5 6 7 8 \nInorder = ");
    PrintInorder(t1);
    printf("\n\n");

    printf("Postorder should be: 2 4 3 6 8 7 5 \nPostorder = ");
    PrintPostorder(t1);
    printf("\n\n");

    printf("Size should be: 7 \n");
    printf("Size = %d \n \n", Size(t1));

    printf("MaxDepth should be: 2 \n");
    printf("MaxDepth = %d \n \n", maxDepth(t1));

    printf("No of leaves should be: 4 \n");
    printf("No of leaves = %d \n \n", NoLeaves(t1));

    printf("Looking for information 4 \n");
    printf("Information from found node = %d \n \n", (Where(t1, 4))->elem );

    printf("Same tree should be: 0 \n");
    printf("Same tree = %d \n\n", sameTree(t1,t2));

    printf("Before swap (mirror). Inorder should be: 2 3 4 5 6 7 8 \n");
    PrintInorder(t1);
    printf("\n");
    mirror(&t1);
    printf("After swap (mirror). Inorder should be: 8 7 6 5 4 3 2 \n");
    PrintInorder(t1);
    printf("\n");

    return 0;
}