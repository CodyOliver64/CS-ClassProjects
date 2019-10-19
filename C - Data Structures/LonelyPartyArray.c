// Cody Oliver
// COP 3502, Spring 2019
// NID: 3125452

#include "LonelyPartyArray.h"
#include <stdio.h>
#include <stdlib.h>

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
  int i, j;

  LonelyPartyArray *party = malloc(sizeof(LonelyPartyArray));

  //Initialize num_fragments and fragment_length using passed variables
  party->num_fragments = num_fragments;
  party->fragment_length = fragment_length;

  //Dynamically allocate fragment array and set each pointer equal to NULL
  party->fragments = malloc(sizeof(int*) * num_fragments);
  for (i = 0; i < num_fragments; i++)
      party->fragments[i] = NULL;

  //Dynamically allocate fragment_sizes array and set each value equal to 0
  party->fragment_sizes = malloc(sizeof(int) * num_fragments);
  for (i = 0; i < num_fragments; i++)
      party->fragment_sizes[i] = 0;

  //Initialize size
  party->size = 0;

  //Initialize num_active_fragments
  party->num_active_fragments = 0;

  //Return Analysis
  if (num_fragments <= 0 || fragment_length <= 0)
    {
      free(party->fragments);
      free(party->fragment_sizes);
      free(party);
      return NULL;
    }
  else if (party == NULL || party->fragments == NULL || party->fragment_sizes == NULL)
    {
      free(party->fragments);
      free(party->fragment_sizes);
      free(party);
      return NULL;
    }
  else
    {
      printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n",
      num_fragments * fragment_length, num_fragments);

      return party;
    }
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
  int i;

  //Return from function if party is NULL
  if (party == NULL)
    return NULL;
  else
    {
      //Free allocated memory
      for (i = 0; i < party->num_fragments; i++)
        if (party->fragments[i] != NULL)
          free(party->fragments[i]);

      free(party->fragments);
      free(party->fragment_sizes);
      free(party);
      printf("-> The LonelyPartyArray has returned to the void.\n");
      return NULL;
    }
}

int set(LonelyPartyArray *party, int index, int key)
{
  int i, row_index, col_index, max_ind, min_ind;

  //Return from function if party is NULL
  if (party == NULL)
    {
      printf("-> Bloop! NULL pointer detected in set().\n");
      return LPA_FAILURE;
    }

  //Establish index parameters
  row_index = index / party->fragment_length;
  col_index = index % party->fragment_length;
  max_ind = (row_index + 1) * party->fragment_length - 1;
  min_ind = row_index * party->fragment_length;

  //Return from function if invalid
  if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
    {
      printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n",
      index, row_index, col_index);

      return LPA_FAILURE;
    }

  //Allocate memory for fragment if fragment is NULL and initalize array to UNUSED
  if (party->fragments[row_index] == NULL)
    {
      party->fragments[row_index] = malloc(sizeof(int) * party->fragment_length);
      for (i = 0; i < party->fragment_length; i++)
        party->fragments[row_index][i] = UNUSED;
      party->num_active_fragments++;

      printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n",
      row_index, party->fragment_length, min_ind, max_ind);
    }

  //Add key to the array, update size if it was UNUSED
  if (party->fragments[row_index][col_index] == UNUSED)
    {
      party->fragments[row_index][col_index] = key;
      party->fragment_sizes[row_index]++;
      party->size++;
      return LPA_SUCCESS;
    }
  else
    {
      party->fragments[row_index][col_index] = key;
      return LPA_SUCCESS;
    }
}

int get(LonelyPartyArray *party, int index)
{
  int row_index, col_index;

  //Return from function if party is NULL
  if (party == NULL)
    {
      printf("-> Bloop! NULL pointer detected in get().\n");
      return LPA_FAILURE;
    }

  //Establish index parameters
  row_index = index / party->fragment_length;
  col_index = index % party->fragment_length;

  //Return from function if invalid
  if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
    {
      printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n",
      index, row_index, col_index);

      return LPA_FAILURE;
    }

  //Return the value at the col_index
  if (party->fragments[row_index] == NULL)
    return UNUSED;
  else
    return party->fragments[row_index][col_index];
}

int printIfValid(LonelyPartyArray *party, int index)
{
  int row_index, col_index;

  //Return LPA_FAILURE if party is NULL
  if (party == NULL)
    return LPA_FAILURE;

  //Establish index parameters
  row_index = index / party->fragment_length;
  col_index = index % party->fragment_length;

  //Return LPA_FAILURE if it there is nothing to print
  if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
    return LPA_FAILURE;
  if (party->fragments[row_index] == NULL)
    return LPA_FAILURE;
  if (party->fragments[row_index][col_index] == UNUSED)
    return LPA_FAILURE;

  printf("%d\n", party->fragments[row_index][col_index]);

  return LPA_SUCCESS;
}

int delete(LonelyPartyArray *party, int index)
{
  int i, row_index, col_index, max_ind, min_ind;

  //Return from function if party is NULL
  if (party == NULL)
    {
      printf("-> Bloop! NULL pointer detected in delete().\n");
      return LPA_FAILURE;
    }

  //Establish index parameters
  row_index = index / party->fragment_length;
  col_index = index % party->fragment_length;
  max_ind = (row_index + 1) * party->fragment_length - 1;
  min_ind = row_index * party->fragment_length;

  //Return from function if invalid
  if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
    {
      printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n",
      index, row_index, col_index);

      return LPA_FAILURE;
    }

  //Return if call is to an unallocated fragment
  if (party->fragments[row_index] == NULL)
    return LPA_FAILURE;

  //Return if cell is already UNUSED
  if (party->fragments[row_index][col_index] == UNUSED)
    return LPA_FAILURE;

  //Set cell to UNUSED
  party->fragments[row_index][col_index] = UNUSED;
  party->fragment_sizes[row_index]--;
  party->size--;

  if (party->fragment_sizes[row_index] == 0)
    {
      free(party->fragments[row_index]);
      party->fragments[row_index] = NULL;
      party->num_active_fragments--;

      printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n",
      row_index, party->fragment_length, min_ind, max_ind);
    }

  return LPA_SUCCESS;

}

int containsKey(LonelyPartyArray *party, int key)
{
  int i, j;

  if (party == NULL)
    return 0;

  for (i = 0; i < party->num_fragments; i++)
    if (party->fragments[i] != NULL)
      for (j = 0; j < party->fragment_length; j++)
        if (party->fragments[i][j] == key)
          return 1;

  return 0;
}

int isSet(LonelyPartyArray *party, int index)
{
  int row_index, col_index;

  //Return from function if party is NULL
  if (party == NULL)
    return 0;

  //Establish index parameters
  row_index = index / party->fragment_length;
  col_index = index % party->fragment_length;

  //Determine if the cell is set
  if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
    return 0;
  if (party->fragments[row_index] == NULL)
    return 0;
  if (party->fragments[row_index][col_index] == UNUSED)
    return 0;

  return 1;
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
  int i, j;

  //Return from function if party is NULL
  if (party == NULL)
    {
      printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
      return party;
    }

  //Set all fragment cells to UNUSED
  for (i = 0; i < party->num_fragments; i++)
    if (party->fragments[i] != NULL)
      for (j = 0; j < party->fragment_length; j++)
        if (party->fragments[i][j] != UNUSED)
          {
            party->fragments[i][j] = UNUSED;
            party->size--;
          }

  //Deallocate any array fragments that are currently active within party
  for (i = 0; i < party->num_fragments; i++)
    if (party->fragments[i] != NULL)
      {
        free(party->fragments[i]);
        party->fragments[i] = NULL;
        party->num_active_fragments--;
      }

  //Reset the fragment_sizes array
  for (i = 0; i < party->num_fragments; i++)
    party->fragment_sizes[i] = 0;

  //Return the reset array
  printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n",
  party->num_fragments * party->fragment_length, party->num_fragments);

  return party;
}

int getSize(LonelyPartyArray *party)
{
  if (party == NULL)
    return -1;
  else
    return party->size;
}

int getCapacity(LonelyPartyArray *party)
{
  if (party == NULL)
    return -1;
  else
    return party->num_fragments * party->fragment_length;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
  if (party == NULL)
    return -1;
  else
    return party->num_active_fragments * party->fragment_length;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
  long long unsigned int total, cell_total;

  if (party == NULL)
    return 0;

  //Perform Long Long Unsigned arithmatic
  cell_total = ((long long unsigned int)party->num_fragments * party->fragment_length);
  total = cell_total * sizeof(int);

  return total;
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
  long long unsigned int lpa_pointer, lpa_struct, lpa_fragments, lpa_fragsize, lpa_activefrag, lpa_nullfrag;

  //Return from function if party is NULL
  if (party == NULL)
    return 0;

  //Perform Long Long Unsigned arithmatic
  lpa_pointer = (long long unsigned int)sizeof(LonelyPartyArray*);
  lpa_struct = (long long unsigned int)sizeof(LonelyPartyArray);
  lpa_fragments = (long long unsigned int)party->num_active_fragments * sizeof(int*);
  lpa_nullfrag = (long long unsigned int)(party->num_fragments - party->num_active_fragments) * sizeof(NULL);
  lpa_fragsize = (long long unsigned int)party->num_fragments * sizeof(int);
  lpa_activefrag = (long long unsigned int)party->num_active_fragments * (party->fragment_length * sizeof(int));

  return (lpa_pointer + lpa_struct + lpa_fragments + lpa_fragsize + lpa_activefrag + lpa_nullfrag);
}

double difficultyRating(void)
{
  double difficulty;
  difficulty = 4.2;
  return difficulty;
}

double hoursSpent(void)
{
  double hours;
  hours = 4.2;
  return hours;
}

LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)  // optional (bonus)
{
  int i, j, cap;

  //Return from function if party is NULL
  if (party == NULL)
    return NULL;

  LonelyPartyArray *c_party = malloc(sizeof(LonelyPartyArray));

  //Initialize num_fragments, fragment_length and size, and num_active_fragments using passed variables
  c_party->num_fragments = party->num_fragments;
  c_party->fragment_length = party->fragment_length;
  c_party->size = party->size;
  c_party->num_active_fragments = party->num_active_fragments;

  //Dynamically allocate fragment array and set each pointer equal to NULL
  c_party->fragments = malloc(sizeof(int*) * party->num_fragments);
  for (i = 0; i < party->num_fragments; i++)
    c_party->fragments[i] = NULL;

  //Dynamically allocate fragment_sizes array and set each value equal to 0
  c_party->fragment_sizes = malloc(sizeof(int) * party->num_fragments);
  for (i = 0; i < party->num_fragments; i++)
    c_party->fragment_sizes[i] = 0;

  //Create fragment pointers and fill fragment cells
  for (i = 0; i < party->num_fragments; i++)
    if (party->fragments[i] != NULL)
      {
        c_party->fragments[i] = malloc(sizeof(int) * party->fragment_length);

        for (j = 0; j < party->fragment_length; j++)
          c_party->fragments[i][j] = party->fragments[i][j];
      }

  //Fill fragment_sizes array
  for (i = 0; i < party->num_fragments; i++)
    c_party->fragment_sizes[i] = party->fragment_sizes[i];

  cap = c_party->num_fragments * c_party->fragment_length;

  printf("-> Successfully cloned the LonelyPartyArray. (capacity: %d, fragments: %d)\n",
  cap, c_party->num_fragments);

  return c_party;

}
