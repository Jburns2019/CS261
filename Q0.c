/* CS261- Assignment 1A - Question 0
   Name: John Burns
   Date: 7/1/19
   Solution description: Valid ;)
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr)
{
  printf("The address iptr is pointing to is: %d. The value at that address is: %d\n", iptr, *iptr);
  
  *iptr += 5;
  
  printf("The address iptr is: %d.\n", &iptr);
}


void fooB(int* jptr)
{
  printf("The address jptr is pointing to is: %d. The value at that address is: %d\n", jptr, *jptr);
  *jptr -= 1;
  printf("The address jptr is: %d.\n", &jptr);
}


int main()
{
  int x = 9;
  printf("The address of x is: %d. The value stored there is: %d.\n", &x, x);
  fooA(&x);
  printf("The value of x is: %d.\n", x);
  // The value of x changed because I passed the address of x to fooA and then changed the value stored at that address.
  fooB(&x);
  printf("The address of x is: %d. The value stored there is: %d.\n", &x, x);
  // The value of x is changed because I passed the address to fooB, but the address did not change. This is because I passed the address and so I have been working with the x address the entire time.  
  return 0;
}


