/***********************************************************
* Author: John Burns && Zhihui Liu
* Email:  burnsjo@oregonState.edu
* Date Created: 7/11/19
* Filename: circularList.c
*
* Overview:
*   This program is a circular doubly linked list implementation
*	of a deque with a front sentinel.
*	It allows for the following behavior:
*		- adding a new link to the front/back
*		- getting the value of the front/back links
*		- removing the front/back link
*		- checking if the deque is empty
*		- printing the values of all the links
*		- reversing the order of the links
*
*	Note that this implementation uses double links (links with
*	next and prev pointers) and that given that it is a circular
*	linked deque the last link points to the sentinel and the first
*	link points to the Sentinel -- instead of null.
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

#ifndef FORMAT_SPECIFIER
#define FORMAT_SPECIFIER "%g"
#endif

// Double link
typedef struct Link
{
	TYPE value;
	struct Link * next;
	struct Link * prev;
} Link;

typedef struct CircularList
{
	int size;
	Link* sentinel;
} CircularList;

/**
  	Allocates the deque's sentinel and sets the size to 0.
  	The sentinel's next and prev should point to the sentinel itself.
 	param: 	deque 	struct CircularList ptr
	pre: 	deque is not null
	post: 	deque sentinel not null
			sentinel next points to sentinel
			sentinel prev points to sentinel
			deque size is 0
 */
static void init(CircularList* deque)
{
	assert(deque != 0);
	deque->sentinel = (Link *)malloc(sizeof(Link));
	deque->size = 0;
	deque->sentinel->next = deque->sentinel;
	deque->sentinel->prev = deque->sentinel;
}

/**
	Creates a link with the given value and NULL next and prev pointers.
	param: 	value 	TYPE
	pre: 	none
	post: 	newLink is not null
			newLink value init to value
			newLink next and prev init to NULL
 */
static Link* createLink(TYPE value)
{
	Link *lnk = (Link *)malloc(sizeof(Link));
	lnk->next = lnk->prev = 0;
	lnk->value = value;
	return lnk;
}

/**
	Adds a new link with the given value after the given link and
	increments the deque's size.
	param: 	deque 	struct CircularList ptr
 	param:	link 	struct Link ptr
 	param: 	TYPE
	pre: 	deque and link are not null
	post: 	newLink is not null
			newLink w/ given value is added after param link
			deque size is incremented by 1
 */
static void addLinkAfter(CircularList* deque, Link* link, TYPE value)
{
	assert(deque != 0 && link != 0);
	Link *lnk = createLink(value);
	lnk->next = link->next;
	lnk->prev = link;
	link->next = lnk;
	lnk->next->prev = lnk;
	deque->size++;
}

/**
	Removes the given link from the deque and decrements the deque's size.
	param: 	deque 	struct CircularList ptr
 	param:	link 	struct Link ptr
	pre: 	deque and link are not null
	post: 	param link is removed from param deque
			memory allocated to link is freed
			deque size is decremented by 1
 */
static void removeLink(CircularList* deque, Link* link)
{
	assert(deque != 0 && link != 0);
	link->prev->next = link->next;
	link->next->prev = link->prev;
	free(link);
	deque->size--;
}

/**
	Allocates and initializes a deque.
	pre: 	none
	post: 	memory allocated for new struct CircularList ptr
			deque init (call to init func)
	return: deque
 */
struct CircularList* circularListCreate()
{
	CircularList* deque = malloc(sizeof(CircularList));
	init(deque);
	return deque;
}

/**
	Deallocates every link in the deque and frees the deque pointer.
	pre: 	deque is not null
	post: 	memory allocated to each link is freed
			" " sentinel " "
			" " deque " "
 */
void circularListDestroy(CircularList* deque)
{
	assert(deque != 0);
	while (deque->size > 0) {
        circularListRemoveFront(deque);
	}
	free(deque->sentinel);
	free(deque);
}

/**
	Adds a new link with the given value to the front of the deque.
	param:	deque 	struct CircularList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ given value before current first link
			(call to addLinkAfter)
 */
void circularListAddFront(CircularList* deque, TYPE value)
{
	assert(deque != 0);
	addLinkAfter(deque, deque->sentinel, value);
}

/**
	Adds a new link with the given value to the back of the deque.
	param: 	deque 	struct CircularList ptr
	param: 	value 	TYPE
	pre: 	deque is not null
	post: 	link is created w/ given value after the current last link
			(call to addLinkAfter)
 */
void circularListAddBack(CircularList* deque, TYPE value)
{
	assert(deque != 0);
	addLinkAfter(deque, deque->sentinel->prev, value);
}

/**
	Returns the value of the link at the front of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	first link's value
 */
TYPE circularListFront(CircularList* deque)
{
	assert(deque != 0 && !circularListIsEmpty(deque));
	return deque->sentinel->next->value;
}

/**
  	Returns the value of the link at the back of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	none
	ret:	last link's value
 */
TYPE circularListBack(CircularList* deque)
{
	assert(deque != 0 && !circularListIsEmpty(deque));
	return deque->sentinel->prev->value;
}

/**
	Removes the link at the front of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	first link is removed and freed (call to removeLink)
 */
void circularListRemoveFront(CircularList* deque)
{
	assert(deque != 0 && !circularListIsEmpty(deque));
	removeLink(deque, deque->sentinel->next);
}

/**
	Removes the link at the back of the deque.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	last link is removed and freed (call to removeLink)
 */
void circularListRemoveBack(CircularList* deque)
{
	assert(deque != 0 && !circularListIsEmpty(deque));
    removeLink(deque, deque->sentinel->prev);
}

/**
	Returns 1 if the deque is empty and 0 otherwise.
	param:	deque	struct CircularList ptr
	pre:	deque is not null
	post:	none
	ret:	1 if its size is 0 (empty), otherwise 0 (not empty)
 */
int circularListIsEmpty(CircularList* deque)
{
    assert(deque != 0);
	return deque->size == 0;
}

/**
	Prints the values of the links in the deque from front to back.
	param:	deque	struct CircularList ptr
	pre:	deque is not null
	post:	none
	ret:	outputs to the console the values of the links from front
			to back; if empty, prints msg that is empty
 */
void circularListPrint(CircularList* deque)
{
	assert(deque != 0);
	if (circularListIsEmpty(deque)) {
        printf("The deque is empty.");
	}
	else { //There are some elements.
        printf("[");
        Link *lnk = deque->sentinel;
        for (int i = 0; i < deque->size; i++) {
            lnk = lnk->next;
            if (i == deque->size - 1) {//end of the list.
                printf("%g]\n", lnk->value);
            }
            else {
                printf("%g, ", lnk->value);
            }
        }
	}
}

/**
	Reverses the deque in place without allocating any new memory.
	The process works as follows: current starts pointing to sentinel;
	tmp points to current's next, current's next points to current's prev,
	current's prev is assigned to tmp and current points to current's next
	(which points to current's prev), so you proceed stepping back through
	the deque, assigning current's next to current's prev, until current
	points to the sentinel then you know the each link has been looked at
	and the link order reversed.
	param: 	deque 	struct CircularList ptr
	pre:	deque is not null
	pre:	deque is not empty
	post:	order of deque links is reversed
 */
void circularListReverse(CircularList* deque) {
	assert(deque != 0 && !circularListIsEmpty(deque));
	Link *current = deque->sentinel;
	Link *tmp;
	for(int i = 0; i <= deque->size; i++) {
        tmp = current->next;
        current->next = current->prev;
        current->prev = tmp;
        current = current->next;
	}
}
