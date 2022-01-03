/* SPDX-License-Identifier: GPL-2.0 */

/* CONSTANTIN MIHAI - 336CA */

typedef char *Key;
typedef char *Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
	Key key;
	Value value;
	struct Element *next;

} Element;

typedef struct HashTable {
	Element **elements;
	long size;
	HashFunction hashFunction;
} HashTable;

int initHashTable(HashTable **hashTable, long size, HashFunction hashFunction)
{
	int i;

	/* alloc memory for hashTable */
	*hashTable = (HashTable *) malloc(sizeof(HashTable));
	if (*hashTable == NULL)
		return 0;

	(*hashTable)->size = size;
	(*hashTable)->hashFunction = hashFunction;

	(*hashTable)->elements = (Element **) malloc(size * sizeof(Element *));
	if ((*hashTable)->elements == NULL)
		return 0;

	for (i = 0; i < size; i++)
		(*hashTable)->elements[i] = NULL;

	return 1;
}

int exists(HashTable *hashTable, Key key)
{
	long idx;
	Element *it;

	idx = hashTable->hashFunction(key, hashTable->size);
	it = hashTable->elements[idx];

	while (it != NULL) {
		if (!strcmp(key, it->key))
			return 1;

		it = it->next;
	}

	return 0;
}

Value get(HashTable *hashTable, Key key)
{
	int idx;
	Element *it;

	idx = hashTable->hashFunction(key, hashTable->size);
	it = hashTable->elements[idx];

	while (it != NULL) {
		if (!strcmp(key, it->key))
			return it->value;

		it = it->next;
	}

	return (Value)0;
}

int put(HashTable *hashTable, Key key, Value value)
{
	int idx;
	Element *it;
	Element *node;
	Element *prev;

	idx = hashTable->hashFunction(key, hashTable->size);
	it = hashTable->elements[idx];

	if (exists(hashTable, key)) {
		while (it != NULL) {
			if (!strcmp(key, it->key)) {
				it->value = value;
				return 1;
			}
			it = it->next;
		}
	}

	/* alloc memory for node */
	node = (Element *) malloc(sizeof(Element));
	if (node == NULL)
		return 0;

	node->key = (char *) malloc(100 * sizeof(char));
	if (node->key == NULL)
		return 0;

	node->value = (char *) malloc(100 * sizeof(char));
	if (node->value == NULL)
		return 0;

	strcpy(node->key, key);
	strcpy(node->value, value);
	node->next = NULL;

	if (!it) {
		/* empty list */
		hashTable->elements[idx] = node;
		return 1;
	}

	prev = NULL;
	while (it != NULL) {
		prev = it;
		it  = it->next;
	}

	prev->next = node;

	return 1;
}

void deleteNode(HashTable *hashTable, Key key)
{
	int idx;
	Element *iterator;
	Element *prev;
	Element *it;
	Element *tmp;

	if (!exists(hashTable, key))
		return;

	idx = hashTable->hashFunction(key, hashTable->size);

	iterator = hashTable->elements[idx];
	prev = NULL;

	if (!strcmp(iterator->key, key)) {

		it = hashTable->elements[idx];
		while (it != NULL) {
			tmp = it;
			it = it->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}

		hashTable->elements[idx] = NULL;
		return;
	}

	while (iterator != NULL) {
		if (!strcmp(iterator->key, key)) {
			prev->next = iterator->next;
			tmp = iterator;
			free(tmp->key);
			free(tmp->value);
			free(tmp);

			return;
		}
		prev = iterator;
		iterator = iterator->next;
	}
}

long hashCode(Key key, long size)
{
	long h = 0;
	unsigned int i;

	for (i = 0; i < strlen(key); i++)
		h = h * 17 + key[i];

	if (h % size < 0)
		return 0;

	return h % size;
}

void freeHashTable(HashTable *hashTable)
{
	int i;
	Element *it;
	Element *tmp;

	if (hashTable == NULL)
		return;

	for (i = 0; i < hashTable->size; i++) {
		it = hashTable->elements[i];
		while (it != NULL) {
			tmp = it;
			it = it->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
	}

	free(hashTable->elements);
	free(hashTable);
}
