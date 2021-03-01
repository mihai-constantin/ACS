// CONSTANTIN MIHAI - 311 CD

#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>

// List element for Dictionary lists.
typedef struct ListNode {
	struct ListNode *next;
	struct ListNode *prev;
	char *key;
	char *value;
	int frequency;
} ListNode;

// Dictionary structure that includes the lists of elements and their number.
typedef struct Dictionary {
	ListNode **lists;		// lists of elements.
	int N;					// number of lists.
} Dictionary;

/* 
tip de date pentru elementele din vectorul v 
	-> folosit pentru sortarea tuplurilor din fiecare lista 
*/
typedef struct Element {
	char *key;
	char *value;
	int frequency;
} Element;

// Initializes an empty Dictionary structure.
Dictionary* createDictionary(int N);

// Adds an element to the Dictionary structure.
void addElement(Dictionary *dictionary, char *key, char *value, int frequency);

// Removes an element from the Dictionary structure.
void removeElement(Dictionary *dictionary, char *key, char *value);

// Prints all the elements from all the lists of the Dictionary structure.
void printDictionary(FILE *f, Dictionary *dictionary);

// Gets all the elements with the specified key and increments the frequencies.
ListNode* get(Dictionary *dictionary, char *key);

// Prints all the elements with the specified value.
void printValue(FILE *f, Dictionary *dictionary , char *value);

// Prints all the elements with the specified frequency.
void printFrequency(FILE *f, Dictionary *dictionary , int frequency);

// Returns a list containing the elements with the specified value.
ListNode* unionValues(Dictionary *dictionary, char *value);

// Returns a list containing the elements with maximum frequency in each list.
ListNode* unionMaxFrequencies(Dictionary *dictionary);

// Returns a new Dictionary with reversed lists of the input structure.
Dictionary* reverseLists(Dictionary *dictionary);

// Prints a double-linked non-circular list.
void printList(FILE *f, ListNode *list);

// Frees all the memory allocated for the Dictionary.
void freeDictionary(Dictionary *dictionary);

// Frees all the memory allocated for a double-linked non-circular list.
void freeList(ListNode *list);

//------------------------------------------------------------------------------

/* Functie folosita pentru a sorta vectorul v conform cerintelor problemei */
int cmp(const void *a, const void *b);

/* Sorteaza elementele din lista conform criteriilor impuse */
void sortare(Dictionary* dictionary);

/* Calculeaza numarul de tupluri aflate la un moment dat in dictionar */ 
int Length_Dictionary(Dictionary* dictionary);

/* 
Adauga elementele in dictionar fara a respecta ordinea impusa 
	-> functie folosita pentru reverseLists(Dictionary* dictionary) 
*/
void addElement2(Dictionary *dictionary, char *key, char *value, int frequency);

/* intoarce lungimea unei liste din dictionar */
int lungime_lista(ListNode* list);

/* intoarce frecventa maxima a tuplurilor dintr-o lista din dicionar */
int MaxFrequency(ListNode* list);

//------------------------------------------------------------------------------

Dictionary* createDictionary(int N) {

	// aloc memorie pentru intreg dictionarul
	Dictionary* dictionary = (Dictionary*) malloc(sizeof(Dictionary));

	if(!dictionary)
		return NULL;

	dictionary -> N = N;

	//aloc memorie pentru toate listele din dictionar
	dictionary -> lists = (ListNode**) malloc(N * sizeof(ListNode*)); 

	if(!dictionary -> lists)
	{
		free(dictionary);
		return NULL;
	}

	for(int i = 0; i < N; i++)
		dictionary -> lists[i] = NULL; // fiecare lista este la inceput vida

	return dictionary;
}

int cmp(const void *a, const void *b)
{
	Element* e1 = (Element*) a;
	Element* e2 = (Element*) b;

	if(e1 -> frequency == e2 -> frequency)
	{
		if(e1 -> value == e2 -> value)
			return strcmp(e1 -> key, e2 -> key); // sortare alfabetica dupa key

		return strcmp(e1 -> value, e2 -> value); // sortare alfabetica dupa value
	}
	else 
	// sortare descrescatoare dupa frequency
		return e2 -> frequency - e1 -> frequency; 
}

void sortare(Dictionary* dictionary)
{
	ListNode *list, *aux;

	for(int i = 0; i < dictionary -> N; i++)
	{
		// calculez nr de elemente din lista i
		int NR = lungime_lista(dictionary -> lists[i]);

		// aloc memorie pentru vectorul v -> NR tupluri
		Element* v = (Element*) malloc(NR * sizeof(Element));

		if(NR > 0)
		{
			// adaug elementele in vectorul v
			list = dictionary -> lists[i];
			aux = list;

			int k = -1;

			while(list)
			{
				k++;
				v[k].key = list -> key;
				v[k].value = list -> value;
				v[k].frequency = list -> frequency;

				list = list -> next;
				if(list == aux)
					break;
			}
		}

		// sortare vector v
		qsort(v, NR, sizeof(Element), cmp);

		// copiez in dictionar vectorul v care contine ordinea corecta a tuplurilor
		list = dictionary -> lists[i];
		aux = list;

		int k = -1;

		while(list)
		{
			k++;

			list -> key = v[k].key;
			list -> value = v[k].value;
			list -> frequency = v[k].frequency;

			list = list -> next;
			if(list == aux)
				break;
		}

		// eliberez memoria alocata pentru vectorul v
		free(v);
	}
}

int Length_Dictionary(Dictionary* dictionary)
{
	if(!dictionary)
		return 0;

	int NR = 0;

	for(int i = 0; i < dictionary -> N; i++)
	{
		ListNode* list = dictionary -> lists[i];
		ListNode* aux = list;

		while(list)
		{
			NR++;

			list = list -> next;
			if(list == aux)
				break;
		}
	}

	return NR;
}

void addElement(Dictionary *dictionary, char *key, char *value, int frequency) {

	// determin lista in care trebuie sa adaug tuplul (key, value, frequency)
	int r = 0;

	for(int i = 0; i < strlen(key); i++)
	{
		r += key[i];
	}

	r = r % dictionary -> N;

	if(dictionary -> lists[r] == NULL) // lista e vida
	{
		ListNode* node = (ListNode*) malloc(sizeof(ListNode));

		if(!node)
			return;

		node -> next = node;
		node -> prev = node;
		node -> frequency = frequency;
		node -> key = key;
		node -> value = value;

		dictionary -> lists[r] = node;
	}
	else
	{
		// lista contine cel putin un element
		int gasit = 0;
		int NR = 0; // numarul de tupluri din lista r

		ListNode* list = dictionary -> lists[r];
		ListNode* aux = list;

		// verific daca in lista exista un tuplu cu aceeasi valoare pentru key si value
		while(list)
		{
			NR++;

			if(!strcmp(list -> value, value)  && !strcmp(list -> key, key))
			{
				list -> frequency += frequency; // adaug la parametrul frequency al tuplului deja existent valoarea frequency
				gasit = 1;
			}

			list = list -> next;

			if(list == aux)
				break;
		}

		if(!gasit)
		{	
			aux = list -> prev;

			// lista contine deja N tupluri -> elimin ultimul element din lista
			if(NR == dictionary -> N) 
			{
				sortare(dictionary); // am grija ca ordinea sa fie corecta inainte de eliminare
				removeElement(dictionary, aux -> key, aux -> value);
			}

			if(!dictionary -> lists[r]) // lista e vida
			{
				ListNode* node = (ListNode*) malloc(sizeof(ListNode));

				if(!node)
					return;

				node -> next = node;
				node -> prev = node;
				node -> frequency = frequency;
				node -> key = key;
				node -> value = value;

				dictionary -> lists[r] = node;
			}
			else // lista contine cel putin un element
			{
				ListNode* node = (ListNode*) malloc(sizeof(ListNode));

				if(!node)
					return;

				node -> next = node;
				node -> prev = node;
				node -> frequency = frequency;
				node -> key = key;
				node -> value = value;

				aux = list -> prev;

				aux -> next = node;
				node -> prev = aux;
				node -> next = list;
				list -> prev = node;
			}

			// verific daca dictionarul contine mai mult de 2 * N tupluri
			int NrTupluri = Length_Dictionary(dictionary);

			if(NrTupluri > 2 * dictionary -> N)
			{
				sortare(dictionary); // ordinea corecta inainte de eliminare

				// elimin din fiecare lista ultimul element
				for(int i = 0; i < dictionary -> N; i++)
				{
					ListNode* list = dictionary -> lists[i];

					if(list)
					{
						ListNode* aux = list -> prev;
						removeElement(dictionary, aux -> key, aux -> value);
					}
				}
			}
		}
	}

	sortare(dictionary);
}

void addElement2(Dictionary *dictionary, char *key, char *value, int frequency) {

	// determin lista in care trebuie sa adaug tuplul
	int r = 0;

	for(int i = 0; i < strlen(key); i++)
	{
		r += key[i];
	}

	r = r % dictionary -> N;

	ListNode* list = dictionary -> lists[r];
	ListNode* aux = list;

	if(!list) // lista e vida
	{
		ListNode* node = (ListNode*) malloc(sizeof(ListNode));

		if(!node)
			return;

		node -> next = node;
		node -> prev = node;
		node -> frequency = frequency;
		node -> key = key;
		node -> value = value;
		
		dictionary -> lists[r] = node;
	}
	else
	{
		ListNode* node = (ListNode*) malloc(sizeof(ListNode));

		if(!node)
			return;

		node -> next = node;
		node -> prev = node;
		node -> frequency = frequency;
		node -> key = key;
		node -> value = value;

		// lista contine cel putin un element
		aux = list -> prev;

		aux -> next = node;
		node -> prev = aux;
		node -> next = list;
		list -> prev = node;
	}
}

int lungime_lista(ListNode* list)
{
	// lista este vida -> nu contine niciun element
	if(!list || !list -> next)
		return 0;

	int NR = 0;

	ListNode* aux = list;

	while(list)
	{
		NR++;

		list = list -> next;
		if(list == aux)
			break;
	}

	return NR;
}

void removeElement(Dictionary *dictionary, char *key, char *value) {
	
	if(!dictionary)
		return;

	// caut in dictionar tuplul de eliminat
	for(int i = 0; i < dictionary -> N; i++)
	{
		ListNode* list = dictionary -> lists[i];
		ListNode* aux = list;

		if(list) // lista nevida
		{
			// elementul pe care trebuie sa il elimin este primul din lista
			if(key == list -> key && value == list -> value)
			{
				if(list -> next == list -> prev && lungime_lista(list) == 1) // lista are un singur element
				{
					ListNode* node = list;
					ListNode* aux2 = node;

					// lista devine vida
					dictionary -> lists[i] = NULL;

					free(aux2); // eliberare memorie 
					return;
				}
				else
				{
					// lista contine cel putin un element
					ListNode* node = list;
					ListNode* aux2 = node;
					
					dictionary -> lists[i] = list -> next;
					dictionary -> lists[i] -> prev = node -> prev;
					node -> prev -> next = dictionary -> lists[i];

					free(aux2); // eliberare memorie
					return;
				}
			}
			else
			{
				while(list)
				{
					if(key == list -> key && value == list -> value)
					{
						ListNode* aux2 = list;

						// am gasit tuplul
						ListNode* aux = list -> prev;

						aux -> next = list -> next;
						list -> next -> prev = aux;

						free(aux2); // eliberare memorie
						return;
					}

					list = list -> next;

					if(list == aux)
						break;
				}	
			}
		}
	}
}

void printDictionary(FILE *f, Dictionary *dictionary) {
	
	if(!f || !dictionary)
		return;

	for(int i = 0; i < dictionary -> N; i++)
	{
		fprintf(f, "List %d: ", i);

		ListNode* list = dictionary -> lists[i];
		ListNode* aux = list;

			while(list)
			{
				fprintf(f, "(%s, %s, %d) ", list -> key, list -> value, list -> frequency);

				list = list -> next;

				if(list == aux)
					break;
			}

		fprintf(f, "\n");
	}
}

ListNode* get(Dictionary *dictionary, char *key) {
	
	int gasit = 0;

	if(!dictionary)
		return NULL;

	ListNode* list = NULL; // lista dublu inlantuita necirculara

	for(int i = 0; i < dictionary -> N; i++)
	{
		ListNode* List = dictionary -> lists[i];
		ListNode* aux = List;

		while(List)
		{
			if(!strcmp(List -> key, key)) // am gasit un tuplu cu cheia key
			{
				gasit = 1;

				ListNode* node = (ListNode*) malloc(sizeof(ListNode));

				node -> next = NULL;
				node -> prev = NULL;
				node -> key = List -> key;
				node -> value = List -> value;
				node -> frequency = List -> frequency;		

				List -> frequency += 1; // incrementare frequency

				//introduc nodul in lista
				if(!list)
				{
					list = node;
				}
				else
				{
					ListNode* pred = NULL; // elementul precedent din lista
					ListNode* aux2 = list;

					// adaug nodul in lista
					while(aux2)
					{
						pred = aux2;
						aux2 = aux2 -> next;
					}

					pred -> next = node;
					node -> prev = pred;
				}
			}

			List = List -> next;

			// conditie iesire lista circulara
			if(List == aux)
				break;
		}
	}

	sortare(dictionary); // sortare necesara (frequency s-a incrementat la elementele cu cheia key)

	if(!gasit)
		return NULL;

	return list;
}

void printValue(FILE *f, Dictionary *dictionary , char *value) {
	
	if(!f || !dictionary)
	{
		fprintf(f, "\n");
		return;
	}

	for(int i = 0; i < dictionary -> N; i++)
	{
		ListNode* list = dictionary -> lists[i];
		ListNode* aux = list;

		while(list)
		{
			if(list -> value == value)
			{
				fprintf(f, "(%s, %s, %d) ", list -> key, list -> value, list -> frequency);
			}

			list = list -> next;

			if(list == aux)
				break;
		}
	}

	fprintf(f, "\n");
}

void printFrequency(FILE *f, Dictionary *dictionary , int frequency) {
	
	if(!f || !dictionary)
	{
		fprintf(f, "\n");
		return;
	}

	for(int i = 0; i < dictionary -> N; i++)
	{
		ListNode* list = dictionary -> lists[i];
		ListNode* aux = list;

		while(list)
		{
			if(list -> frequency == frequency)
			{
				fprintf(f, "(%s, %s, %d) ", list -> key, list -> value, list -> frequency);
			}

			list = list -> next;

			if(list == aux)
				break;
		}
	}

	fprintf(f, "\n");
}

ListNode* unionValues(Dictionary *dictionary, char *value) {

	int gasit = 0;
	
	if(!dictionary)
		return NULL;

	ListNode* list = NULL; // lista dublu inlantuita necirculara

	for(int i = 0; i < dictionary -> N; i++)
	{
		ListNode* List = dictionary -> lists[i];
		ListNode* aux = List;

		while(List)
		{
			if(!strcmp(List -> value, value))
			{
				gasit = 1;
					
				ListNode* node = (ListNode*) malloc(sizeof(ListNode));

				node -> next = NULL;
				node -> prev = NULL;
				node -> key = List -> key;
				node -> value = List -> value;
				node -> frequency = List -> frequency;

				if(!list) // lista e vida
				{
					list = node;
				}
				else
				{
					ListNode* pred = NULL;
					ListNode* aux2 = list;

					// adaug nodul in lista
					while(aux2)
					{
						pred = aux2;
						aux2 = aux2 -> next;
					}

					pred -> next = node;
					node -> prev = pred;
				}
			}

			List = List -> next;

			if(List == aux)
				break;
		}
	}

	if(!gasit)
		return NULL;

	return list;
}

int MaxFrequency(ListNode* list)
{
	if(!list)
		return 0;

	int ans = 0;

	ListNode* aux = list;

	while(list)
	{
		if(ans < list -> frequency)
			ans = list -> frequency;

		list = list -> next;

		if(list == aux)
			break;
	}

	return ans;
}

ListNode* unionMaxFrequencies(Dictionary *dictionary) {
	
	if(!dictionary)
		return NULL;

	ListNode* list = NULL; // lista dublu inlantuita necirculara

	int gasit = 0;

	for(int i = 0; i < dictionary -> N; i++)
	{
		ListNode* List = dictionary -> lists[i];
		ListNode* aux = List;

		int maxFrequency = MaxFrequency(List);

		while(List)
		{
			if(List -> frequency == maxFrequency)
			{
				gasit = 1;

				ListNode* node = (ListNode*) malloc(sizeof(ListNode));

				node -> next = NULL;
				node -> prev = NULL;
				node -> key = List -> key;
				node -> value = List -> value;
				node -> frequency = List -> frequency;

				//introduc nodul in lista

				if(!list) // lista e vida
				{
					list = node;
				}
				else
				{
					ListNode* pred = NULL;
					ListNode* aux2 = list;

					// adaug nodul in lista
					while(aux2)
					{
						pred = aux2;
						aux2 = aux2 -> next;
					}

					pred -> next = node;
					node -> prev = pred;
				}
			}

			List = List -> next;

			// conditie iesire lista circulara
			if(List == aux)
				break;
		}
	}

	if(!gasit)
		return NULL;

	return list;
}

Dictionary* reverseLists(Dictionary *dictionary) {
	
	if(!dictionary)
		return NULL;

	Dictionary* reverse_dictionary = createDictionary(dictionary -> N);

	for(int i = 0; i < dictionary -> N; i++)
	{
		if(dictionary -> lists[i])
		{
			ListNode* list = dictionary -> lists[i] -> prev; // nodul de pornire este ultimul
			ListNode* aux = list;

			while(aux)
			{
				// adaug elementul in lista
				addElement2(reverse_dictionary, aux -> key, aux -> value, aux -> frequency);

				aux = aux -> prev;

				if(aux == list)
					break;
			}
		}
	}

	return reverse_dictionary;
}

void printList(FILE *f, ListNode *list) {
	
	if(!f || !list)
	{
		fprintf(f, "\n");
		return;
	}

	while(list)
	{
		fprintf(f, "(%s, %s, %d) ", list -> key, list -> value, list -> frequency);

		list = list -> next;
	}

	fprintf(f, "\n");
}

void freeDictionary(Dictionary *dictionary) {
	
	if(!dictionary)
		return;

	int N = dictionary -> N;

	for(int i = 0; i < N; i++)
	{
		// eliberez memorie pentru fiecare lista in parte
		ListNode* list = dictionary -> lists[i];
		ListNode* aux = list;

		while(list)
		{
			ListNode* node = list;

			list = list -> next;

			free(node);

			if(list == aux)
				break;
		}
	}

	free(dictionary -> lists);
	free(dictionary);
	dictionary = NULL;
}

void freeList(ListNode *list) {

	if(!list)
		return;

	while(list)
	{
		ListNode* node = list;

		list = list -> next;

		free(node);
	}

	free(list);
	list = NULL;
}

#endif
