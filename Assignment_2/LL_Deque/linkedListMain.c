#include "linkedList.c"
#include <stdio.h>

int main(){
	struct LinkedList* l = linkedListCreate();
	printf("This list is empty: %d\n", linkedListIsEmpty(l));
	linkedListAddFront(l, (TYPE)1);
	linkedListAddBack(l, (TYPE)2);
	linkedListAddBack(l, (TYPE)3);
	linkedListAddFront(l, (TYPE)4);
	linkedListAddFront(l, (TYPE)5);
	linkedListAddBack(l, (TYPE)6);
	printf("This list is not empty: %d\n", linkedListIsEmpty(l));
	linkedListPrint(l);
	printf("%i\n", linkedListFront(l));
	printf("%i\n", linkedListBack(l));
	linkedListRemoveFront(l);
	linkedListRemoveBack(l);
	linkedListPrint(l);
        linkedListDestroy(l);
/* BAG */

      struct LinkedList* k = linkedListCreate();
       linkedListAdd (k, (TYPE)10);
       linkedListAdd (k, (TYPE)11);
        linkedListAdd (k, (TYPE)13);
       linkedListAdd(k, (TYPE)14);
       linkedListRemove(k, (TYPE)11);
       printf("k contains 10: %d\n", linkedListContains(k, (TYPE)10));
       printf("k doesn't contain 11: %d\n", !linkedListContains(k, (TYPE)11));
       printf("k contains 13: %d\n", linkedListContains(k, (TYPE)13));
       printf("k contains 14: %d\n", linkedListContains(k, (TYPE)14));
        linkedListPrint(k);
        linkedListDestroy(k);
	return 0;
}

