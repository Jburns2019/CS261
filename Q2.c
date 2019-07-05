/* CS261- Assignment 1A - Question 2
   Name: John Burns
   Date: 07/01/19
   Solution description: gonna work with some foos's.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c)
{
    int *temp = a;
    a = b;
    b = temp;

    c --;
    return c;
}

int main()
{
    int x = rand() % 11;
    int y = rand() % 11;
    int z = rand() % 11;
    printf("(x, y, z): (%d, %d, %d).\n", x, y, z);
    int val = foo(&x, &y, z);
    printf("(x, y, z): (%d, %d, %d).\n", x, y, z);
    printf("c is: %d", val);
    return 0;
}

// Yes. The return value is different because a copy of c was given to foo and so only the copy was changed not the original.
// No. Though a change of addresses did occur, the address swap was applied to a copy of the pointers not the actual x and y.
