/* CS261- Assignment 1A - Question 1
   Name: John Burns
   Date: 7/1/19
   Solution description: Make some students.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student
{
	int id;
	int score;
};

struct student* allocate()
{
  return (struct student *) malloc(10 * sizeof(struct student));
}

void generate(struct student* students)
{
    for (int i = 0; i < 10; i++) {
    //find id.
      int rndId = (rand() % 10) + 1;
      
      int j = 0;
      students[0].id = rndId;
      int searching = 1;
      while (j < 10 && searching == 1) {
        if (students[j].id == rndId) {
          rndId = (rand() % 10) + 1;
          j = -1;
        }
        j++;
        if (j == 10) {
          students[i].id = rndId;
          searching = 0;
        }
      }

      // find score.
      int rndScore = rand() % 101;
      j = 0;
      searching = 1;
      while (j < 10 && searching == 1) {
        if (students[j].score == rndScore) {
          rndId = rand() % 101;
          j = -1;
        }
        j++;
        if (j == 10) {
          students[i].score = rndScore;
          searching = 0;
        }
      }
    }
}

void output(struct student* students)
{
    for (int i = 0; i < 10; i++) {
      printf("ID%d: %d Score%d: %d.\n", i + 1, students[i].id, i + 1, students[i].score);
    }
}

void summary(struct student* students)
{
  int average = 0;
  int max = -1;
  int min = 101;

  for (int i = 0; i < 10; i++) {
    int val = students[i].score;
    average += val;
    if (val > max) {
      max = val;
    }
    if (val < min) {
      min = val;
    }
  }

  average /= 10;

  printf("\nThe average score is: %d.\nThe maximum score is: %d.\nThe minimum score is: %d.\n", average, max, min);
}

void deallocate(struct student* stud)
{
     if (stud != NULL) {
       free(stud);
     }
}

int main()
{
    struct student* stud = NULL;
    stud = allocate();
    generate(stud);
    output(stud);
    summary(stud);
    deallocate(stud);
    return 0;
}
