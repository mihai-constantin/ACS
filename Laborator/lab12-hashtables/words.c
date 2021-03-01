#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  
    *h = (HashTable*) malloc(sizeof(HashTable));
    
    (*h) -> size = size;
    (*h) -> hashFunction = f;
    
    (*h) -> elements = (Element**) malloc(size * sizeof(Element*));
    for(int i = 0; i < size; i++)
        (*h) -> elements[i] = NULL;
}

int exists(HashTable *hashTable, Key key) {
  
    long idx = hashTable -> hashFunction(key, hashTable -> size);
    
    Element* iterator = hashTable -> elements[idx];
    
    while(iterator != NULL)
    {
        if(!strcmp(key, iterator -> key))
            return 1;
        
        iterator = iterator -> next;
    }
    
    return 0;
}

Value get(HashTable *hashTable, Key key) {
  
    int idx = hashTable -> hashFunction(key, hashTable -> size);
    
    Element* iterator = hashTable -> elements[idx];
    
    while (iterator != NULL)
    {
        if(!strcmp(key, iterator -> key))
            return iterator -> value;
        
        iterator = iterator -> next;
    }
    
    return (Value)0;
}

void put(HashTable *hashTable, Key key, Value value) {
    
    int idx = hashTable -> hashFunction(key, hashTable -> size);
    
    Element* iterator = hashTable -> elements[idx];
  
    if(exists(hashTable, key))
    {
        while (iterator)
        {
            if(!strcmp(key, iterator -> key))
            {
                iterator -> value = value;
                return;
            }
            
            iterator = iterator -> next;
        }
    }
    
    /* aloc memorie pentru un nod nod */
    Element* node = (Element*) malloc(sizeof(Element));
    
    node -> key = key;
    node -> value = value;
    node -> next = NULL;
    
    if(!iterator)
    {
        /* lista este vida */
        hashTable -> elements[idx] = node;
    }
    
    Element* prev = NULL;
    
    while(iterator != NULL)
    {
        prev = iterator;
        iterator = iterator -> next;
    }
    
    prev -> next = node;
}

void deleteKey(HashTable *hashTable, Key key) {
  
    if(!exists(hashTable, key))
        return;
    
    int idx = hashTable -> hashFunction(key, hashTable -> size);
    
    Element* iterator = hashTable -> elements[idx];
    Element* prev = NULL;
    
    if(!strcmp(iterator -> key, key))
    {
        hashTable -> elements[idx] = NULL;
        return;
    }
    
    while (iterator != NULL)
    {
        if(!strcmp(iterator -> key, key))
        {
            prev -> next = iterator -> next;
            return;
        }
        
        prev = iterator;
        iterator = iterator -> next;
    }
}

void print(HashTable *hashTable) {
  
    for(int i = 0; i < hashTable -> size; i++)
    {
        printf("%d: ", i);
        
        // parcurg fiecare lista din hashTable
        Element* iterator = hashTable -> elements[i];
        
        while (iterator != NULL)
        {
            printf("%s ", iterator -> key);
            iterator = iterator -> next;
        }
        
        printf("\n");
    }
}

void freeHashTable(HashTable *hashTable) {
  // Cerinta 1
}


long hash1(Key word, long size) {
  
    long h = 0;
    
    for(int i = 0; i < strlen(word); i++)
        h = h * 17 + word[i];
    
    return h % size;
}

int main(int argc, char* argv[]) {
    
    HashTable *hashTable, *h1, *h2;
    FILE *f1, *f2;
    char word[256];
    long hashSize, common;

    hashSize = atoi(argv[1]);
    f1 = fopen(argv[2], "r");
    f2 = fopen(argv[3], "r");

    initHashTable(&hashTable, hashSize, &hash1);
    
    // creez cele doua tabele hash
    initHashTable(&h1, hashSize, &hash1);
    initHashTable(&h2, hashSize, &hash1);
    
    int freq;
    while(fscanf(f1, "%s", word) != EOF) {
        if(exists(h1, word) == 0)
            freq = 1;
        else
            freq = get(h1, word) + 1;
        put(h1, word, freq);
    }
    
    print(h1);
    print(h2);

  // Cerinta 3

  // ...

  // Cerinta 4

  // ...

  printf("Common words: %ld\n", common);

  fclose(f1);
  fclose(f2);
  return 0;
}
