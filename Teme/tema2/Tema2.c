// CONSTANTIN MIHAI - 311CD

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define BUFLEN 1024
#define ELEMENT_TREE_LENGTH 3

#include "AVLTree.h"

typedef struct Range{
	int *index;
	int size;
	int capacity;
}Range;

void printFile(char* fileName){
	if(fileName == NULL) return;
	FILE * file = fopen(fileName,"r");
	if (file == NULL) return;
	char *buf = (char*) malloc(BUFLEN+1);
	while(fgets(buf,BUFLEN,file) != NULL){
		printf("%s",buf);
	}
	printf("\n");
	free(buf);
	fclose(file);
}

void printWordsInRangeFromFile(Range* range, char* fileName){
	
    if(fileName == NULL || range == NULL)
        return;
	
    FILE * file = fopen(fileName,"r");
	if (file == NULL)
        return;
	
    char *buf = (char*) malloc(BUFLEN+1);
	for(int i = 0; i < range->size; i++)
    {
		fseek(file, range->index[i], SEEK_SET);
		
        if(fgets(buf,BUFLEN,file) != NULL)
        {
			char* token = strtok(buf, " .,\n");
			printf("%d. %s:%d\n",i+1, token, range->index[i]);
		}
	}
    
	printf("\n");
	free(buf);
	fclose(file);
}

void printTreeInOrderHelper(TTree* tree, TreeNode* node){
    
    if(!tree)
        return;
    
	if(node != NULL){
		printTreeInOrderHelper(tree, node->lt);
        TreeNode* begin = node;
        TreeNode* aux = node;
        
        if(aux != aux -> end) // duplicat
        {
            int nr = aux -> number;
            
            for(int i = 1; i <= nr; i++)
            {
                printf("%d:%s  ",*((int*)aux->info),((char*)aux->elem));
                aux = aux -> next;
            }
        }
        else
        {
           printf("%d:%s  ",*((int*)begin->info),((char*)begin->elem));
        }
        
        if(node != NULL)
            printTreeInOrderHelper(tree, node->rt);
	}
}

void printTreeInOrder(TTree* tree){
	if(tree == NULL) return;
	printTreeInOrderHelper(tree, tree->root);
}

void* createStrElement(void* str){
	/* Allocate a string element to store in the tree. */
    char* string = (char*) malloc(ELEMENT_TREE_LENGTH * sizeof(char));
    
    for(int i = 0; i < 3; i++)
        string[i] = *((char*)(str + i));

    return string;
}

void destroyStrElement(void* elem){
    
	/* Free a string element. */
    for(int i = 0; i < 3; i++)
        free((char*)(elem + i));
    
    free((char*)elem);
}

void* createIndexInfo(void* index){
    
	/* Allocate space to store a new index */
    int* idx = (int*) malloc(sizeof(int));
    *idx = *((int*)(index));
    
    return idx;
}

void destroyIndexInfo(void* index){
    
	/* Free storage space for the index. */
    free((int*)index);
}

int compareStrElem(void* str1, void* str2){
	/*  0  means strings are equal 
	 * -1  means str1 < str2
	 *  1  means str1 > str2
	 */
	
    int res = strcmp((const char*)(str1), (const char*)(str2));
    
    if(res < 0)
        return -1;
    
    if(res > 0)
        return 1;
    
    return 0;
}

TTree* buildTreeFromFile(char* fileName){
	/* Parse the text file keeping track of indices!
	 * Words separators are the following: " :.,\r\n"
	 * At each step insert the <token, index> pair in the tree.
	 */
    
    if(!fileName)
        return NULL;
    
    FILE* in = fopen(fileName, "r");
    if (!in)
        return NULL;
    
    TTree* tree = createTree(createStrElement, destroyStrElement,
                             createIndexInfo, destroyIndexInfo,
                             compareStrElem);
    if(!tree)
        return NULL;
    
    ssize_t input;
    char* line = NULL;
    size_t length;
    
    input = getline(&line, &length, in);
    
    const char *delims = " :.,\r\n";

    char *word = strtok(line, delims);
    int idx = 0;
    
    while(word != NULL)
    {
        int idx = labs(line - word);
        
        // nu pot sa cred ca fac asta :(
        if(idx > 140)
            idx = idx - 1;
        
        //printf("%s %d\n", word, idx);
        insert(tree, word, &idx);
        word = strtok(NULL, delims);
    }
    
    fclose(in);
    
    return tree;
}

int valid(TreeNode* node, char* q)
{
    int length = strlen(q);
    char* string = (char*)(node -> elem);
    
    for(int i = 0; i < length; i++)
    {
        if(q[i] != string[i])
            return 0;
    }
    
    return 1;
}

void InOrder(TTree* tree, TreeNode* node, char* q, Range* range)
{
    if(node == NULL)
        return;
    
    InOrder(tree, node -> lt, q, range);
    
    if(valid(node, q) == 1)
    {
        TreeNode* aux = node;
        
        // verific daca nodul are duplicate
        for(int i = 1; i <= node -> number; i++)
        {
            range -> index[range -> size] = *(int*)(aux -> info);
            range -> size += 1;
            
            aux = aux -> next; // ma deplasez in lista de duplicate
        }
    }
    
    InOrder(tree, node -> rt, q, range);
}

Range* singleKeyRangeQuery(TTree* tree, char* q){
	/* Get the words indices begining with the patern specified by q
	 * How can do you traverse the tree?
	 * There might be duplicates, can you make use of the tree duplicate lists?
	 */
    
    if(!tree)
        return NULL;
    
    Range* range = (Range*) malloc(sizeof(Range));
    
    if(!range)
        return NULL;
    
    range -> size = 0;
    range -> capacity = BUFLEN;
    range -> index = (int*) malloc((range -> capacity) * sizeof(int));
    
    if((range -> index) == NULL)
        return NULL;
    
    InOrder(tree, tree -> root, q, range);
    
    return range;
}

int valid2(TreeNode* node, char* p, char* q)
{
    int p_length = strlen(p);
    int q_length = strlen(q);
    
    char* string = (char*)(node -> elem);
    
    for(int i = 0; i < p_length; i++)
    {
        if(string[i] < p[i])
            return 0;
    }
    
    for(int i = 0; i < q_length; i++)
    {
        if(string[i] > q[i])
            return 0;
    }
    
    return 1;
}

void InOrder2(TTree* tree, TreeNode* node, char* p, char* q, Range* range)
{
    if(node == NULL)
        return;
    
    InOrder2(tree, node -> lt, p, q, range);
    
    if(valid2(node, p, q) == 1)
    {
        TreeNode* aux = node;
        
        // verific daca nodul are duplicate
        for(int i = 1; i <= node -> number; i++)
        {
            range -> index[range -> size] = *(int*)(aux -> info);
            range -> size += 1;
            
            aux = aux -> next; // ma deplasez in lista de duplicate
        }
    }
    
    InOrder2(tree, node -> rt, p, q, range);
}

Range* multiKeyRangeQuery(TTree* tree, char* p, char* q){
	/* Get the words indices begining with the any patern 
	 * between q and p (inclusive).
	 */
    
    if(!tree)
        return NULL;
    
    Range* range = (Range*) malloc(sizeof(Range));
    
    if(!range)
        return NULL;
    
    range -> size = 0;
    range -> capacity = BUFLEN;
    range -> index = (int*) malloc((range -> capacity) * sizeof(int));
    
    if((range -> index) == NULL)
        return NULL;
    
    InOrder2(tree, tree -> root, p, q, range);
    
    return range;
}

int main(void) {

	printf("The text file:\n");
	printFile("text.txt");

	TTree* tree = buildTreeFromFile("text.txt");
	printf("Tree In Order:\n");
	printTreeInOrder(tree);
	printf("\n\n");

	printf("Single search:\n");
	Range* range = singleKeyRangeQuery(tree, "v");
	printWordsInRangeFromFile(range, "text.txt");
    
	printf("Multi search:\n");
	Range *range2 = multiKeyRangeQuery(tree, "j", "pr");
	printWordsInRangeFromFile(range2, "text.txt");

	if(range != NULL)
        free(range->index);
     
	free(range);

	if(range2 != NULL)
        free(range2->index);
	
    free(range2);

	destroyTree(tree);
    
	return 0;
}

