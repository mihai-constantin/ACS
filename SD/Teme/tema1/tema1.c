#include <stdio.h>
#include <string.h>
#include "Dictionary.h"

void easy_0() {
	FILE *f = fopen("test_easy_0.txt", "w");
	if (f == NULL) {
		printf("Error opening file test_easy_0!\n");
		return;
	}

	Dictionary *dictionary = createDictionary(4);
	printDictionary(f, dictionary);
	
	Dictionary *reversedDictionary = reverseLists(dictionary);
	printDictionary(f, reversedDictionary);
	
	freeDictionary(reversedDictionary);
	freeDictionary(dictionary);
	fclose(f);
}

void easy_1() {
	FILE *f = fopen("test_easy_1.txt", "w");
	if (f == NULL) {
		printf("Error opening file test_easy_1!\n");
		return;
	}

	Dictionary *dictionary = createDictionary(4);
	addElement(dictionary, "key1", "value1", 20);
	addElement(dictionary, "key2", "value2", 30);
	addElement(dictionary, "key3", "value3", 15);
	addElement(dictionary, "key4", "value4", 20);
	printDictionary(f, dictionary);
	printFrequency(f, dictionary , 20);
	printValue(f, dictionary , "value4");

	if (dictionary && dictionary->lists && dictionary->lists[0]) {
		fprintf(f, "%d\n", dictionary->lists[0] == dictionary->lists[0]->prev);
	}
	
	Dictionary *reversedDictionary = reverseLists(dictionary);
	printDictionary(f, reversedDictionary);
	
	freeDictionary(reversedDictionary);
	freeDictionary(dictionary);
	fclose(f);
}

void easy_2() {
	FILE *f = fopen("test_easy_2.txt", "w");
	if (f == NULL) {
		printf("Error opening file test_easy_1!\n");
		return;
	}

	Dictionary *dictionary = createDictionary(4);
	addElement(dictionary, "key1", "value1", 20);
	addElement(dictionary, "key2", "value2", 30);
	addElement(dictionary, "key3", "value3", 15);
	addElement(dictionary, "key4", "value4", 20);
	printDictionary(f, dictionary);
	printValue(f, dictionary , "value4");

	removeElement(dictionary, "key3", "value3");
	addElement(dictionary, "key3", "value4", 50);
	printValue(f, dictionary , "value4");

	Dictionary *reversedDictionary = reverseLists(dictionary);
	printDictionary(f, reversedDictionary);

	freeDictionary(reversedDictionary);
	freeDictionary(dictionary);
	fclose(f);
}

void medium_1() {
	FILE *f = fopen("test_medium_1.txt", "w");
	if (f == NULL) {
		printf("Error opening file test_medium_1!\n");
		return;
	}

	Dictionary *dictionary = createDictionary(4);
	addElement(dictionary, "key1", "value1", 20);
	addElement(dictionary, "key1", "value2", 20);
	addElement(dictionary, "key1", "value3", 20);
	addElement(dictionary, "key1", "value4", 20);
	addElement(dictionary, "key1", "value5", 20);
	printDictionary(f, dictionary);
	removeElement(dictionary, "key1", "value0");
	removeElement(dictionary, "key1", "value2");
	removeElement(dictionary, "key1", "value5");
	addElement(dictionary, "key1", "value0", 20);
	printDictionary(f, dictionary);
	printValue(f, dictionary , "value4");

	ListNode *list = get(dictionary, "key1");
	printList(f, list);
	freeList(list);
	list = unionValues(dictionary, "value0");
	printList(f, list);
	freeList(list);
	list = unionValues(dictionary, "value6");
	printList(f, list);
	freeList(list);
	list = unionMaxFrequencies(dictionary);
	printList(f, list);
	freeList(list);

	addElement(dictionary, "key1", "value1", 20);

	list = unionMaxFrequencies(dictionary);
	printList(f, list);
	freeList(list);
	printDictionary(f, dictionary);

	Dictionary *reversedDictionary = reverseLists(dictionary);
	printDictionary(f, reversedDictionary);

	freeDictionary(reversedDictionary);
	freeDictionary(dictionary);
	fclose(f);
}

void medium_2() {
	FILE *f = fopen("test_medium_2.txt", "w");
	if (f == NULL) {
		printf("Error opening file test_medium_2!\n");
		return;
	}

	Dictionary *dictionary = createDictionary(4);
	addElement(dictionary, "key1", "value1", 20);
	addElement(dictionary, "key1", "value2", 20);
	addElement(dictionary, "key1", "value3", 20);
	addElement(dictionary, "key1", "value4", 20);
	addElement(dictionary, "key1", "value5", 20);
	removeElement(dictionary, "key1", "value2");
	removeElement(dictionary, "key1", "value5");
	addElement(dictionary, "key1", "value0", 20);

	ListNode *list = get(dictionary, "key2");
	printList(f, list);
	freeList(list);
	printFrequency(f, dictionary , 21);
	addElement(dictionary, "key1", "value0", 20);
	printDictionary(f, dictionary);
	printFrequency(f, dictionary , 21);

	Dictionary *reversedDictionary = reverseLists(dictionary);
	printDictionary(f, reversedDictionary);

	freeDictionary(reversedDictionary);
	freeDictionary(dictionary);

	dictionary = createDictionary(4);
	addElement(dictionary, "key", "value1", 20);
	addElement(dictionary, "key", "value0", 20);
	addElement(dictionary, "key", "value2", 30);
	addElement(dictionary, "key", "value3", 15);
	addElement(dictionary, "key4", "value1", 20);
	addElement(dictionary, "key1", "value1", 20);
	addElement(dictionary, "key1", "value0", 20);
	addElement(dictionary, "key1", "value2", 30);
	addElement(dictionary, "key1", "value3", 15);
	addElement(dictionary, "key14", "value1", 20);
	addElement(dictionary, "key", "value", 30);
	printDictionary(f, dictionary);
	list = get(dictionary, "key");
	printList(f, list);
	freeList(list);
	list = get(dictionary, "key14");
	printList(f, list);
	freeList(list);
	printDictionary(f, dictionary);
	list = get(dictionary, "key1");
	printList(f, list);
	freeList(list);
	list = get(dictionary, "key1");
	printList(f, list);
	freeList(list);
	list = unionMaxFrequencies(dictionary);
	printList(f, list);
	freeList(list);
	printDictionary(f, dictionary);
	printFrequency(f, dictionary, 77);
	printFrequency(f, dictionary, 21);
	printValue(f, dictionary, "value1");
	printValue(f, dictionary, "value4");
	list = unionValues(dictionary, "value777");
	printList(f, list);
	freeList(list);
	list = unionValues(dictionary, "value0");
	printList(f, list);
	freeList(list);
	freeDictionary(dictionary);

	fclose(f);
}

void complex_1() {
	FILE *f = fopen("test_complex_1.txt", "w");
	if (f == NULL) {
		printf("Error opening file test_complex_1!\n");
		return;
	}

	Dictionary *dictionary = createDictionary(9);
	addElement(dictionary, "key333", "value333", 33);
	addElement(dictionary, "key333", "value303", 22);
	addElement(dictionary, "key333", "value330", 44);
	addElement(dictionary, "key333", "value331", 22);
	addElement(dictionary, "key333", "value033", 22);
	addElement(dictionary, "key396", "value033", 22);
	addElement(dictionary, "key000", "value033", 22);
	addElement(dictionary, "key333", "value306", 44);
	addElement(dictionary, "key333", "value336", 44);
	addElement(dictionary, "key000", "value336", 44);
	addElement(dictionary, "key396", "value336", 44);
	printDictionary(f, dictionary);
	freeDictionary(dictionary);

	dictionary = createDictionary(1);
	addElement(dictionary, "key", "value", 3);
	addElement(dictionary, "key", "value", 2);
	addElement(dictionary, "key", "value", 1);
	printDictionary(f, dictionary);
	addElement(dictionary, "key", "value1", 1);
	printDictionary(f, dictionary);
	freeDictionary(dictionary);

	dictionary = createDictionary(5);
	addElement(dictionary, "key555", "value555", 55);
	addElement(dictionary, "key555", "value555", 77);
	addElement(dictionary, "key555", "value555", 44);
	addElement(dictionary, "key555", "value555", 60);
	addElement(dictionary, "key555", "value555", 50);
	addElement(dictionary, "key555", "value444", 44);
	addElement(dictionary, "key555", "value777", 44);
	addElement(dictionary, "key555", "value333", 77);
	addElement(dictionary, "key555", "value777", 77);
	addElement(dictionary, "key555", "value", 55);
	addElement(dictionary, "key", "value", 55);
	addElement(dictionary, "key444", "value444", 44);
	addElement(dictionary, "key777", "value444", 44);
	addElement(dictionary, "key444", "value000", 44);
	addElement(dictionary, "key444", "value777", 77);
	addElement(dictionary, "key777", "value777", 77);
	addElement(dictionary, "key555", "value888", 77);
	addElement(dictionary, "key444", "value000", 44);
	addElement(dictionary, "key222", "value000", 77);
	printDictionary(f, dictionary);

	ListNode *list = unionMaxFrequencies(dictionary);
	printList(f, list);
	freeList(list);
	printFrequency(f, dictionary, 77);
	list = get(dictionary, "key777");
	printList(f, list);
	freeList(list);
	printDictionary(f, dictionary);
	list = get(dictionary, "key222");
	printList(f, list);
	freeList(list);
	printDictionary(f, dictionary);
	list = get(dictionary, "key2");
	printList(f, list);
	freeList(list);
	printFrequency(f, dictionary, 122);
	printValue(f, dictionary, "value777");
	list = unionValues(dictionary, "value777");
	printList(f, list);
	freeList(list);
	list = unionValues(dictionary, "value27");
	printList(f, list);
	freeList(list);
	printValue(f, dictionary, "value23");
	printDictionary(f, dictionary);

	Dictionary *reversedDictionary = reverseLists(dictionary);
	printDictionary(f, reversedDictionary);

	Dictionary *identicalDictionary = reverseLists(reversedDictionary);
	printDictionary(f, identicalDictionary);
	freeDictionary(reversedDictionary);

	removeElement(dictionary, "key555", "value555");
	removeElement(dictionary, "key555", "value555");
	removeElement(dictionary, "key555", "value555");
	removeElement(dictionary, "key555", "value555");
	removeElement(dictionary, "key555", "value555");
	removeElement(dictionary, "key555", "value444");
	removeElement(dictionary, "key555", "value333");
	removeElement(dictionary, "key555", "value777");
	removeElement(dictionary, "key555", "value");
	removeElement(dictionary, "key", "value");
	removeElement(dictionary, "key444", "value444");
	removeElement(dictionary, "key777", "value444");
	removeElement(dictionary, "key444", "value000");
	removeElement(dictionary, "key444", "value777");
	removeElement(dictionary, "key777", "value777");
	removeElement(dictionary, "key555", "value888");
	removeElement(dictionary, "key444", "value000");
	removeElement(dictionary, "key222", "value000");
	printDictionary(f, dictionary);

	reversedDictionary = reverseLists(dictionary);
	printDictionary(f, reversedDictionary);

	freeDictionary(reversedDictionary);
	freeDictionary(identicalDictionary);
	freeDictionary(dictionary);
	fclose(f);
}

void complex_2() {
	FILE *f = fopen("test_complex_2.txt", "w");
	if (f == NULL) {
		printf("Error opening file test_complex_2!\n");
		return;
	}

	Dictionary *dictionary = createDictionary(4);
	addElement(dictionary, "key0", "value1", 20);
	addElement(dictionary, "key0", "value2", 20);
	removeElement(dictionary, "key0", "value1");
	removeElement(dictionary, "key0", "value2");
	addElement(dictionary, "key0", "value2", 20);
	addElement(dictionary, "key0", "value1", 20);
	removeElement(dictionary, "key0", "value1");
	removeElement(dictionary, "key0", "value2");
	addElement(dictionary, "key0", "value1", 20);
	addElement(dictionary, "key0", "value2", 20);
	addElement(dictionary, "key1", "value3", 20);
	addElement(dictionary, "key1", "value4", 20);
	addElement(dictionary, "key2", "value5", 20);
	addElement(dictionary, "key2", "value6", 20);
	addElement(dictionary, "key3", "value7", 20);
	addElement(dictionary, "key3", "value8", 20);
	printDictionary(f, dictionary);
	removeElement(dictionary, "key2", "value6");
	removeElement(dictionary, "key3", "value8");
	addElement(dictionary, "key4", "value1", 20);
	addElement(dictionary, "key8", "value1", 20);
	addElement(dictionary, "key1", "value3", 20);
	addElement(dictionary, "key9", "value3", 20);
	printDictionary(f, dictionary);
	freeList(get(dictionary, "key8"));
	printDictionary(f, dictionary);
	freeList(get(dictionary, "key0"));
	printDictionary(f, dictionary);
	freeList(get(dictionary, "key4"));
	printDictionary(f, dictionary);
	freeList(get(dictionary, "key1"));
	printDictionary(f, dictionary);
	freeList(get(dictionary, "key1"));
	printDictionary(f, dictionary);
	ListNode *list = unionMaxFrequencies(dictionary);
	printList(f, list);
	freeList(list);
	addElement(dictionary, "key9", "value3", 22);
	printDictionary(f, dictionary);
	addElement(dictionary, "key9", "value3", 2);
	addElement(dictionary, "key1", "value3", 1);
	printDictionary(f, dictionary);
	freeList(get(dictionary, "key1"));
	printDictionary(f, dictionary);
	freeList(get(dictionary, "key1"));
	printDictionary(f, dictionary);
	list = unionValues(dictionary, "value3");
	printList(f, list);
	freeList(list);
	printValue(f, dictionary, "value3");
	addElement(dictionary, "key4", "value1", 3);
	printFrequency(f, dictionary, 24);
	addElement(dictionary, "key0", "value0", 3);
	printDictionary(f, dictionary);
	freeList(get(dictionary, "key0"));
	printDictionary(f, dictionary);
	freeDictionary(dictionary);
	fclose(f);
}

int main() {
	//easy_0();
	//easy_1();
	//easy_2();
	//medium_1();
	//medium_2();
	//complex_1();
	//complex_2();

	return 0;
}
