#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#ifndef TYPE
#define TYPE double
#endif

#ifndef LT
#define LT(A, B) ((A) < (B))
#endif

#ifndef EQ
#define EQ(A, B) ((A) == (B))
#endif

typedef struct CircularList CircularList;

CircularList* circularListCreate();
void circularListDestroy(CircularList* list);
void circularListPrint(CircularList* list);
void circularListReverse(CircularList* list);

// Deque interface

void circularListAddFront(CircularList* list, TYPE value);
void circularListAddBack(CircularList* list, TYPE value);
TYPE circularListFront(CircularList* list);
TYPE circularListBack(CircularList* list);
void circularListRemoveFront(CircularList* list);
void circularListRemoveBack(CircularList* list);
int circularListIsEmpty(CircularList* list);

#endif
