// Cody Oliver
// COP 3502, Spring 2019
// NID: 3125452

#include "DupeyDupe.h"
#include <stdio.h>
#include <string.h>

// Return the projects difficulty rating
double difficultyRating(void)
 {
   double diff = 4.0;
   return diff;
 }

// Return the hours spent on the project
 double hoursSpent(void)
 {
   double time = 3.5;
   return time;
 }

int main(int argc, char **argv)
{
  int i, j, dup_flag = 0, match_flag = 0;

  // Check for consecutive dupe dupe, set flag to 1 when found
  for (i=1; i<argc-1; i++)
    if (strcmp (argv[i], "dupe") == 0 && strcmp (argv[i], argv[i+1]) == 0)
      dup_flag = 1;

  // Check for duplicates starting at the end of the list and print the last one
  for (i=argc-1; i> 1; i--)
    for (j=i-1; j>= 1; j--)
      if (strcmp (argv[i], argv[j]) == 0 && match_flag == 0)
      {
        printf("%s\n", argv[i]);
        match_flag = 1;
      }

  // Print dupe dupe if found
  if (dup_flag == 1)
    printf("dupe dupe!\n");

// Print no dupe if no duplicates were found
  if (match_flag == 0 && dup_flag == 0)
    printf("no dupey dupe :(\n");

  difficultyRating();
  hoursSpent();

  return 0;
}
