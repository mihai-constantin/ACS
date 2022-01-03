#include <stdio.h>

typedef int T;
#include "SortedList.h"

SortedList* getNaturals(int A, int B) {
  SortedList* nats;
  int i;
  init(&nats);
  for (i = A; i <= B; i++) {
    insert(&nats, i);
  }
  return nats;
}

SortedList* getPrimes(int N) {
  SortedList* nats = getNaturals(2, N);

  // TODO: Cerința 4

  /*
  
  // Metoda 1

  int i, j;

  for(i = 2; i * i <= N; i++)
    if(contains(nats, i))
      for(j = i * i; j <= N; j += i)
        deleteOnce(&nats, j);

  return nats;

  */

  // Metoda 2

  SortedList* primes;

  init(&primes);

  SortedList* aux = nats;

  while(!isEmpty(nats))
  {
    if(isEmpty(primes))
    {
        insert(&primes, nats -> value);
        deleteOnce(&nats, nats -> value);
    }
    else
    {
        aux = primes;

        while(aux != NULL)
        {
            if(nats -> value % aux -> value == 0)
            {
                deleteOnce(&nats, nats -> value);
                break;
            }

            aux = aux -> next;
        }

        if(!aux)
        {
            insert(&primes, nats -> value);
            deleteOnce(&nats, nats -> value);
        }
    }
  }

  return primes;
  
}

void printInts(SortedList* list) {
  while (!isEmpty(list)) {
    printf("%d ", list->value);
    list = list->next;
  }
  printf("\n");
}

int main(int argc, char* argv[]) {
  printInts(getPrimes(100));
  return 0;
}
