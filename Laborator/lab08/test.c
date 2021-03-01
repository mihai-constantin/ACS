#include <stdio.h>

/* Need the define before including such that Item means something. */
#define Item int
#include "heap.h"

#define ASSERT(cond, msg) if (!(cond)) { failed(msg); return 0; }
void passed(char* s) {
    printf("Testul %s a fost trecut cu succes!\t\t \n", s);
}

void failed(char* s) {
    printf("Testul %s NU a fost trecut!\n", s);
}


int main() {
    APriQueue q = makeQueue(1);

    ASSERT(q->size == 0, "Init-01");
    ASSERT(q->capacity == 1, "Init-02");
    ASSERT(q->elem != NULL, "Init-03");

    passed("Init");

    insert(q, (ItemType) { 0, 0 });
    ASSERT(getMax(q).prior == 0, "Insert-01");

    insert(q, (ItemType) { 1, 1 });
    ASSERT(getMax(q).prior == 1, "Insert-02");

    insert(q, (ItemType) { 2, 2 });
    ASSERT(getMax(q).prior == 2, "Insert-03");

    insert(q, (ItemType) { 3, 3 });
    ASSERT(getMax(q).prior == 3, "Insert-04");

    ASSERT(q->size == 4, "Insert-05");

    passed("Insert");

    ASSERT(removeMax(q).prior == 3, "Remove-01");
    ASSERT(removeMax(q).prior == 2, "Remove-02");
    ASSERT(removeMax(q).prior == 1, "Remove-03");
    ASSERT(removeMax(q).prior == 0, "Remove-04");
    ASSERT(q->size == 0, "Remove-05");

    passed("Remove");

    return 0;
}

