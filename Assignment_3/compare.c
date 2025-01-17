#include <stdio.h>
#include "bst.h"
#include "structs.h"
#include <string.h>

/*----------------------------------------------------------------------------
 very similar to the compareTo method in java or the strcmp function in c. it
 returns an integer to tell you if the left value is greater then, less then, or
 equal to the right value. you are comparing the number variable, letter is not
 used in the comparison.

 if left < right return -1
 if left > right return 1
 if left = right return 0
 */

 /*Define this function, type casting the value of void * to the desired type.
  The current definition of TYPE in bst.h is void*, which means that left and
  right are void pointers. To compare left and right, you should first cast
  left and right to the corresponding pointer type (struct data *), and then
  compare the values pointed by the casted pointers.

  DO NOT compare the addresses pointed by left and right, i.e. "if (left < right)",
  which is really wrong.
 */
int compare(TYPE left, TYPE right)
{
    int returnVal = 0;
    if (right == left) {
        returnVal = 0;
    }
    else {
        struct data *rVal = (struct data *)right;
        struct data *lVal = (struct data *)left;
        returnVal = rVal->number - lVal->number;
        if (returnVal == 0 && strlen(rVal->name) != strlen(lVal->name)) {
            returnVal = (strlen(rVal->name) - strlen(lVal->name));
        }
        if (returnVal < 0) {
            returnVal = -1;
        } else if (returnVal > 0) {
            returnVal = 1;
        }
    }
	return returnVal;

}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval)
{
    struct data *val = (struct data*)curval;
    if (val->number != NULL) {
        printf("[int]");
    }
    if (val->small != NULL) {
        printf("[short]");
    }
    if (strlen(val->name) > 0) {
        printf("[string]");
    }

}
