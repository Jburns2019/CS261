#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#ifndef TYPE
#define TYPE int
#endif

#ifndef LT
#define LT(A, B) ((A) < (B))
#endif

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif

typedef struct LinkedList LinkedList;

LinkedList* linkedListCreate();
void linkedListDestroy(LinkedList* list);
void linkedListPrint(LinkedList* list);

// Deque interface

int linkedListIsEmpty(LinkedList* list);
void linkedListAddFront(LinkedList* list, TYPE value);
void linkedListAddBack(LinkedList* list, TYPE value);
TYPE linkedListFront(LinkedList* list);
TYPE linkedListBack(LinkedList* list);
void linkedListRemoveFront(LinkedList* list);
void linkedListRemoveBack(LinkedList* list);

// Bag interface

void linkedListAdd(LinkedList* list, TYPE value);
int linkedListContains(LinkedList* list, TYPE value);
void linkedListRemove(LinkedList* list, TYPE value);

#endif
