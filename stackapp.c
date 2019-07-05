/*	stack.c: Stack application. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynamicArray.c"

/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
*/
char nextChar(char* s) {
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' ) {
		return '\0';
	}
	else {
		return c;
	}
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre:
	post:
*/

int isBalanced(char* s) {
    DynArr *opener = newDynArr(5);

    char ch = nextChar(s);

    while (ch != '\0') {
        if (ch == '(' || ch == '{' || ch == '[') {
            pushDynArr(opener, ch);
        }
        else if((topDynArr(opener) == '(' && ch == ')') ||
                (topDynArr(opener) == '[' && ch == ']') ||
                (topDynArr(opener) == '{' && ch == '}')) {
            popDynArr(opener);
        }

        ch = nextChar(s);
    }

	return isEmptyDynArr(opener);
}

int main(int argc, char* argv[]) {
    int res;
    char* s;
    if (argv[1] != NULL && argc > 0) {
        s=argv[1];

        printf("Assignment 2\n");

        res = isBalanced(s);
    }
    else {
        res = 1;
        s= "";
    }
	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);


	return 0;
}

