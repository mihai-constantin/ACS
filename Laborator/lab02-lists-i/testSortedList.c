#include <stdio.h>
#include <assert.h>

typedef long T;
#include "SortedList.h"

// -----------------------------------------------------------------------------

#define ASSERT(cond, msg) if (!(cond)) { failed(msg); return 0; }

void passed(char* s, float score) {
  printf("Testul %s a fost trecut cu succes!\t Puncte: %.2f\n", s, score);
}

void failed(char* s) {
  printf("Testul %s NU a fost trecut!\n", s);
}

// -----------------------------------------------------------------------------

int testInit(SortedList** slist,  float score) {                   // tests init
  init(slist);
  ASSERT((*slist) == NULL, "Init-01");
  ASSERT(isEmpty(*slist) == 1, "IsEmpty-01");
  printf(". ");

  passed("Init&IsEmpty", score);
  return 1;
}

int testInsert(SortedList** slist, float score) {                // tests insert
  init(slist);
  insert(slist, 1l);
  ASSERT((*slist)->value == 1l, "Insert-01")
  printf(". ");

  insert(slist, 2l);
  ASSERT((*slist)->value == 1l, "Insert-02")
  ASSERT((*slist)->next->value == 2l, "Insert-02")
  printf(". ");

  insert(slist, -1l);
  ASSERT((*slist)->value == -1l, "Insert-03")
  ASSERT((*slist)->next->value == 1l, "Insert-04")
  printf(". ");

  insert(slist, 0l);
  ASSERT((*slist)->value == -1l, "Insert-05")
  ASSERT((*slist)->next->value == 0l, "Insert-06")
  printf(". ");


  passed("Insert", score);
  return 1;
}

int testLength(SortedList** slist, float score) {                // tests length
  long idx;
  init(slist);
  ASSERT(length(*slist) == 0, "Length-01")
  printf(". ");

  for(idx = 2; idx <= 10; idx += 2) {
    insert(slist, idx);
    insert(slist, idx);
    ASSERT(length(*slist) == idx, "Length-02")
  }
  printf(". ");

  insert(slist, 0l);
  ASSERT(length(*slist) == 11, "Length-03")
  printf(". ");

  insert(slist, 0l);
  ASSERT(length(*slist) == 12, "Length-03")
  printf(". ");

  passed("Length", score);
  return 1;
}

int testContains(SortedList** slist, float score) {            // tests contains
  long idx;
  init(slist);
  ASSERT(length(*slist) == 0, "Contains-01")
  printf(". ");

  for(idx = 12; idx >= -10; idx -= 1) {
    ASSERT(contains(*slist, idx) == 0, "Contains-02")
    insert(slist, idx);
    ASSERT(contains(*slist, idx) == 1, "Contains-03")
  }
  printf(". ");

  ASSERT(length(*slist) == 23, "Contains-04")
  printf(". ");

  passed("Contains", score);
  return 1;
}

int testDeleteOnce(SortedList** slist, float score) {        // tests deleteOnce
  long idx;
  init(slist);
  deleteOnce(slist, 2l);
  ASSERT(isEmpty(*slist), "DeleteOnce-01")

  for(idx = 1; idx <= 10; idx++) {
    ASSERT(contains(*slist, idx) == 0, "DeleteOnce-02")
    insert(slist, idx);
    insert(slist, idx);
    ASSERT(contains(*slist, idx) == 1, "DeleteOnce-03")
    deleteOnce(slist, idx);
    ASSERT(contains(*slist, idx) == 1, "DeleteOnce-04")
  }
  printf(". ");

  for(idx = 10; idx >= 1; idx-=2) {
    ASSERT(contains(*slist, idx) == 1, "DeleteOnce-05")
    deleteOnce(slist, idx);
    ASSERT(contains(*slist, idx) == 0, "DeleteOnce-06")
  }

  for(idx = 1; idx <= 10; idx+=2) {
    ASSERT(contains(*slist, idx) == 1, "DeleteOnce-07")
    deleteOnce(slist, idx);
    ASSERT(contains(*slist, idx) == 0, "DeleteOnce-08")
  }
  printf(". ");

  ASSERT(isEmpty(*slist) == 1, "DeleteOnce-09")

  passed("DeleteOnce", score);
  return 1;
}

int testGetNth(SortedList** slist, float score) {                // tests getNth
  long idx;
  init(slist);
  for(idx = 1; idx <= 10; idx++) {
    insert(slist, idx);
    ASSERT(getNth(*slist, idx) == idx, "GetNth-01")
  }
  printf(". ");

  for(idx = 2; idx <= 10; idx+=2) {
    deleteOnce(slist, idx);
  }
  printf(". ");

  for(idx = 9; idx >= 1; idx-=2) {
    ASSERT(getNth(*slist, (idx+1)/2) == idx, "GetNth-02")
  }
  printf(". ");

  ASSERT(getNth(*slist, length(*slist)) == 9l, "GetNth-03")
  printf(". ");

  passed("GetNth", score);
  return 1;
}


int testMega(SortedList** slist, float score) {              // tests everything
  long idx;
  init(slist);
  ASSERT(isEmpty(*slist) == 1, "Mega-01")
  ASSERT(length(*slist) == 0, "Mega-02")
  ASSERT(contains(*slist, 0l) == 0, "Mega-03")
  printf(".");

  insert(slist, 3l);
  ASSERT(length(*slist) == 1, "Mega-04")
  ASSERT(getNth(*slist, 1) == 3l, "Mega-05")
  ASSERT(contains(*slist, 3l) == 1, "Mega-06")
  printf(".");

  insert(slist, 4l);
  ASSERT(length(*slist) == 2, "Mega-07")
  ASSERT(getNth(*slist, 1) == 3l, "Mega-08")
  printf(".");

  insert(slist, 2l);
  ASSERT(length(*slist) == 3, "Mega-09")
  ASSERT(getNth(*slist, 3) == 4l, "Mega-10")
  ASSERT(getNth(*slist, 1) == 2l, "Mega-11")
  printf(".");

  ASSERT(contains(*slist, 2l) == 1, "Mega-12")
  ASSERT(contains(*slist, 3l) == 1, "Mega-13")
  ASSERT(contains(*slist, 4l) == 1, "Mega-14")
  ASSERT(contains(*slist, 5l) == 0, "Mega-15")
  printf(".");

  deleteOnce(slist, 3l);
  ASSERT(contains(*slist, 2l) == 1, "Mega-16")
  ASSERT(contains(*slist, 3l) == 0, "Mega-17")
  ASSERT(contains(*slist, 4l) == 1, "Mega-18")
  ASSERT(length(*slist) == 2, "Mega-19")
  ASSERT(getNth(*slist, 2) == 4l, "Mega-20")
  printf(".");

  deleteOnce(slist, 3l);
  ASSERT(contains(*slist, 2l) == 1, "Mega-21")
  ASSERT(contains(*slist, 3l) == 0, "Mega-22")
  ASSERT(contains(*slist, 4l) == 1, "Mega-23")
  ASSERT(length(*slist) == 2, "Mega-24")
  ASSERT(getNth(*slist, 2) == 4l, "Mega-25")
  printf(".");

  deleteOnce(slist, 2l);
  ASSERT(contains(*slist, 2l) == 0, "Mega-26")
  ASSERT(contains(*slist, 4l) == 1, "Mega-27")
  ASSERT(length(*slist) == 1, "Mega-28")
  ASSERT(getNth(*slist, 1) == 4l, "Mega-29")
  printf(".");

  deleteOnce(slist, 4);
  ASSERT(isEmpty(*slist) == 1, "Mega-30")
  printf(". ");

  passed("Mega", score);
  return 1;
}


// -----------------------------------------------------------------------------
// Special test: frees the memory allocated for all lists

int testFree(long listsNo, SortedList** slist, float score) {
  long listIdx;
  for (listIdx = 0; listIdx < listsNo; listIdx++) {
    freeSortedList(&(slist[listIdx]));
    printf(".");
  }
  printf(" *Programul se va verifica cu valgrind*\t Puncte: %.2f.\n", score);
  return 1;
}

// -----------------------------------------------------------------------------

typedef struct Test {
  int (*testFunction)(SortedList**, float);
  float score;
} Test;

int main(int argc, char* argv[]) {
  Test tests[] =                                    // Define the tests you want
    {
      { &testInit, 0.05 },
      { &testInsert, 0.2 },
      { &testLength, 0.05 },
      { &testContains, 0.05 },
      { &testDeleteOnce, 0.2 },
      { &testGetNth, 0.05 },
      { &testMega, 0.1 }
    };

  float totalScore = 0.0f, maxScore = 0.0f;
  long testsNo = sizeof(tests) / sizeof(Test);
  long testIdx;
  SortedList** testLists = (SortedList**) malloc(sizeof(SortedList*) * testsNo);

  for (testIdx = 0; testIdx < testsNo; testIdx++) {
    float score = tests[testIdx].score;
    if ((*(tests[testIdx].testFunction))(&(testLists[testIdx]), score)) {
      totalScore += score;
    }
    maxScore += score;
  }

  if (testFree(testsNo, testLists, 0.1))
    totalScore += 0.1;
  maxScore += 0.1;

  printf("\nScor total: %.2f / %.2f\n\n", totalScore, maxScore);

  free(testLists);
  return 0;
}
