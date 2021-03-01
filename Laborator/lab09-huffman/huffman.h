#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int

#define INF 1000005

// Including below so `Item` is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {
    
    // initializare vector freqs
    for(int i = 0; i < 256; i++)
        freqs[i] = 0;
    
    // formare vector freqs
    for(int i = 0; i < size; i++)
        freqs[(int)(text[i])]++;
    /*
    for(int i = 0; i < 256; i++)
        printf("%d %d\n", i, freqs[i]);
    */
}

HuffmanNode* makeTree(int freqs[256], int* size) {
    
    // calculez cate frunze am
    for(int i = 0; i < 256; i++)
        if(freqs[i] != 0)
            (*size)++;
    
    // alocare vector nodes
    HuffmanNode* nodes = (HuffmanNode*) malloc((*size) * sizeof(HuffmanNode));
    
    if(!nodes)
        return NULL;
    
    // alocare minHeap
    APriQueue minHeap = makeQueue((*size));
    
    int nr = -1;
    
    // creez cate un nod huffman pentru fiecare frunza
    for(int i = 0; i < 256; i++)
        if(freqs[i] != 0)
        {
            nr++;
            nodes[nr].value = (char)(i);
            nodes[nr].left = -1;
            nodes[nr].right = -1;
            
            // adaug in minHeap
            ItemType x;
            x.prior = freqs[i];
            x.content = nr;
            
            //printf("%d %d\n", x.prior, x.content);
            
            //printf("%c %d\n", (char)(i), freqs[i]);
            
            insert(minHeap, x);
        }
    
    while(minHeap -> size >= 2)
    {
        ItemType node_1 = removeMin(minHeap);
        ItemType node_2 = removeMin(minHeap);
        
        // creez un nod huffman care are copii pe node_1 si pe node_2
        if(nr + 1 == (*size))
        {
            // realocare
            nodes = (HuffmanNode*) realloc(nodes, 2 * (*size) * sizeof(HuffmanNode));
        }
        
        (*size)++;
        nodes[(*size) - 1].left = node_1.content;
        nodes[(*size) - 1].right = node_2.content;
        
        // adaug in minHeap
        ItemType x;
        x.prior = node_1.prior + node_2.prior;
        x.content = (*size) - 1;
        
        insert(minHeap, x);
    }
    
    return nodes;
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code)
{
    if (nodes[index].left == -1 && nodes[index].right == -1) {
        codes[(int)nodes[index].value] = strdup(code);
    }
    else {
        int n = strlen(code);
        if (nodes[index].left != -1) {
            code[n] = '0';
            code[n + 1] = '\0';
            makeCodes(nodes[index].left, nodes, codes, code);
            code[n] = '\0';
        }
        
        if (nodes[index].right != -1) {
            code[n] = '1';
            makeCodes(nodes[index].right, nodes, codes, code);
            code[n] = '\0';
            code[n + 1] = '\0';
        }
    }
}

int findChar(HuffmanNode *nodes, int numNodes, char c)
{
    int i;
    for (i = 0; i < numNodes; i++)
        if (nodes[i].value == c)
            return i;
}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes)
{
    if (numNodes == 0)
        return calloc(1, sizeof(char));
    
    char *compressed = calloc(numNodes * 100, sizeof(char));
    
    char **codes = calloc(256, sizeof(char *));
    char *code = calloc(100, sizeof(char));
    
    makeCodes(numNodes - 1, nodes, codes, code);
    
    
    int pos;
    int i;
    for (i = 0; i < textSize; i++) {
        pos = findChar(nodes, numNodes, text[i]);
        strcat(compressed, codes[(int)nodes[pos].value]);
    }
    
    for (i = 0; i < 256; i++)
        if (codes[i])
            free(codes[i]);
    free(codes);
    free(code);
    
    return compressed;
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes)
{
    char *decompressed = calloc(100, sizeof(char));
    if (numNodes == 0)
        return decompressed;
    
    int i; HuffmanNode node = nodes[numNodes - 1];
    
    for (i = 0; i < textSize; i++) {
        if (node.left == -1 && node.right == -1) {
            decompressed[strlen(decompressed)] = (char)node.value;
            node = nodes[numNodes - 1];
        }
        
        if (text[i] == '0')
            node = nodes[node.left];
        else
            node = nodes[node.right];
    }
    
    if (node.left == -1 && node.right == -1)
        decompressed[strlen(decompressed)] = (char)node.value;
    
    return decompressed;
}

#endif

