/*
Cody Oliver (UCF ID 3125452)
COP 3223 - 0R06
Assignment #7 - Codebreaking
11/10/2018
*/

//pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function Prototypes - do not change these
void greeting();
void setParameters(int * length, int * difficulty);
int * createHideList(int length, int difficulty);
int * createShowList(int length);
void display(int showlist[], int length);
void getGuess(int guess[], int length);
void processGuess(int hidelist[], int showlist[], int length, int guess[]);
int solved(int hidelist[], int guess[], int length);
int PerfectMatches(int hidelist[], int guess[], int length);
int ImperfectMatches(int hidelist[], int guess[], int length);
void copyArray(int dest[], int source[], int length);

//Main function - This is the final version of main.  Any changes you make while
//creating the functions should be removed prior to submission.
int main() {
    //Length determines the number of hidden values that must be guessed
    //Difficulty determines the range of the hidden values
    int length, difficulty;
    //Answer, revealed, and guess are all integer arrays
    //Since length is undefined at this point, no sizes have been assigned.
    //This will be done in the create...List functions.
    //Answer is the correct answer of the hidden values
    //Revealed is the list that is shown to the user
    //Guess is the user's guess
    int * answer, * revealed, * guess;

    //seed the random number generator
    srand(time(0));

    //Begin the program by showing the initial greeting to the user
    greeting();

    //Ask the user for the length and difficulty
    setParameters(&length, &difficulty);

    //Create the initial arrays of size length
    answer = createHideList(length, difficulty);
    revealed = createShowList(length);
    guess = createShowList(length);

    printf("\nThere are %d numbers ranging from 1 to %d.\n\n", length, difficulty*3);

    //Loop until the user solves the puzzle
    while (!solved(answer, guess, length)) {
        //Show the information gathered so far and prompt the user for their next guess
        display(revealed, length);
        getGuess(guess, length);
        processGuess(answer, revealed, length, guess);
    }

    printf("Congratulations! You guessed all the values!\n\n");

    //These functions are necessary because we are using memory allocation functions in create...List
    free(answer);
    free(revealed);
    free(guess);

    return 0;
}

//Functions
//Pre-conditions:  none
//Post-conditions: Prints a welcome message to the screen
void greeting() {
    printf("Welcome to Codebreaker Training!\n\n");
    printf("You will be presented with a set of hidden values.  Your job is to guess these\n");
    printf("values and their correct order. After each guess you will be given feedback.\n\n");
    printf("Values that are correct in magnitude and in the correct location\nwill be revealed.  These are ");
    printf("perfect matches.\n\nThen you will be told how many other numbers are correct in magnitude only.\n");
    printf("These are imperfect matches. No additional information will be revealed.\n\n");
    return;
}

//Pre-conditions:  length and difficulty are valid values established by the setParameters function
//Post-conditions: create an array of size length and populate it with random
//                 values based on the difficulty
int * createHideList(int length, int difficulty) {
    //i is a counter
    //array is an integer array, allocated "length" integers
    int i;
    int * array = (int *)malloc(sizeof(int) * length);

    //traverse the valid indices of the array
    //assign each index a random value from 1 - difficulty*3
    for(i=0; i<length; i++)
        array[i] = rand() % (difficulty*3) + 1;

    //return the beginning of the array to the main function
    return array;
}

//Pre-conditions:  length has a valid value established by the setParameters function
//Post-conditions: create an array of size length and initialize to zero
int * createShowList(int length){
    //i is a counter
    //array is an integer array, allocated "length" integers
    int i;
    int * array = (int *)malloc(sizeof(int) * length);

    //traverse the valid indices of the array
    //assign each index an initial value of 0
    for(i=0; i<length; i++)
        array[i] = 0;

    //return the beginning of the array to the main function
    return array;
}

//Pre-conditions:  length and difficulty are integer pointers
//Post-conditions: length and difficulty will be set by the user
//                 Function should verify that these values are valid

//What to do in this function: Prompt the user for the length of the code.  Remember
//that the parameter length is a pointer, so it cannot store an integer value.  You may need additional
//variables.  Ensure that the user gives you a value between 5 and 10, inclusive.  If their
//value is invalid, continue to prompt them until they provide a valid one.  Assign this value to the location
//that length is pointing at.  Repeat this process for the difficulty parameter.  Difficulty
//must be 1, 2, or 3 to continue.
void setParameters(int * length, int * difficulty) {
    int lengt = 0, diff = 0;

    //prompt user for length of code
    while (lengt < 5 || lengt > 10){
        printf("\nChoose a length for the code (5-10 numbers).\n");
        scanf("%d", &lengt);
    }

    //prompt user for difficulty
    while (diff < 1 || diff > 3){
        printf("\nChoose a difficulty (1, 2, or 3).\n");
        scanf("%d", &diff);
    }

    //assign values to length and difficulty
    *length = lengt;
    *difficulty = diff;

    return;
}

//Pre-conditions:  showlist is an integer array of size length
//Post-conditions: displays the contents of showlist using - for 0

//What to do in this function: Traverse the showlist array and print a - whenever the value is 0
//If the value is not zero, print the actual value.  For example, if the code is 12311 and the
//user has identified the location of the 1s, the showlist/revealed array will contain 10011
//and you should display 1--11
void display(int showlist[], int length) {
    int i;

    //initialize the showlist with dashes if zero or values when guessed
    for (i=0; i<length; i++){
        if (showlist[i] == 0)
            printf("-");
        else
            printf("%d", showlist[i]);
    }

    printf("\n");

    return;

}

//Pre-conditions:  guess is an integer array of size length
//Post-conditions: reads in the guess from a user as a string and converts it to an integer array

//What to do in this function: The user will enter their values all together.  For example: 12311
//Read this in as a string and then store each individual integer value in the guess array.
//Since the elements of the input will be characters, you will need to convert to integers.  For example
//you  would need to convert from '1' to 1. Character representations of digits start with '0' with ASCII value 48.
void getGuess(int guess[], int length) {
    int i;
    char lguess[length];

    //prompt user for their guess as a string
    printf("Enter your guess:");
    scanf("%s", lguess);

    //convert string to values and assign them to the guess array
    for (i=0; i<length; i++)
        guess[i] = (lguess[i] - 48);

    return;

}

//Pre-conditions:  both hidelist and guess are integer arrays of size length
//                 hidelist represents the answer the user is looking for
//                 guess represents the user's current guess
//Post-conditions: determines if the user has found all of the hidden values

//What to do in this function: Traverse the arrays and check to see if all of the values
//in hidelist are the same as the values in guess.  If they are return 1 for true,
//return 0 for false otherwise.
int solved(int hidelist[], int guess[], int length) {
    int i, nomatch = 1;

    //check to see if there's an exact match and update flag if there is not
    for (i=0; i<length; i++)
        if (hidelist[i] != guess[i])
            nomatch = 0;

    //return 1 if there is an exact match and 0 if there is not
    if (nomatch == 0)
        return 0;
    else
        return 1;

}

//Pre-conditions:  hidelist, showlist, and guess are integer arrays of size length
//                 hidelist represents the answer the user is looking for
//                 showlist shows the values the user has already discovered
//                 guess is the user's current guess
//Post-conditions: evaluates the current guess and updates showlist

//What to do in this function: Compare hidelist to guess.  If any values match exactly,
//update the showlist to reflect the information the user has discovered.  Then, print out
//the number of perfect matches the user has by calling the PerfectMatches function.  Print
//out the number of imperfect matches the user has by calling the ImperfectMatches function.
//Use the statement from the samples for your printf control string.
void processGuess(int hidelist[], int showlist[], int length, int guess[]) {
    int i, imp_num, per_num;

    //update the shown list if there is a perfect match
    for (i=0; i<length; i++)
        if (hidelist[i] == guess[i])
            showlist[i] = guess [i];

    //print the number of perfect matches by calling their functions
    imp_num = ImperfectMatches(hidelist, guess, length);
    per_num = PerfectMatches(hidelist, guess, length);

    printf("You have %d perfect matches and %d imperfect matches.\n\n", per_num, imp_num);

}

//Pre-conditions:  hidelist and guess are integer arrays of size length
//                 hidelist represents the answer the user is looking for
//                 guess is the user's current guess
//Post-conditions: evaluates the current guess and returns the number of perfect matches

//What to do in this function: Compare hidelist to guess. Return the number of times
//the value in guess exactly matches the corresponding value in hidelist.
int PerfectMatches(int hidelist[], int guess[], int length) {
    int i, num_match=0;

    //determine the number of perfect matches
    for (i=0; i<length; i++)
        if (guess[i] == hidelist[i])
            num_match++;

    return num_match;

}

//Pre-conditions:  hidelist and guess are integer arrays of size length
//                 hidelist represents the answer the user is looking for
//                 guess is the user's current guess
//Post-conditions: evaluates the current guess and returns the number of imperfect matches

//What to do in this function: Create temporary copies of both arrays by calling the copyArray function
//twice.  This is necessary because we'll need to make changes to both arrays without modifying the
//originals.  Mark out the spots on the arrays that match exactly.  They will be counted in the perfect
//matches instead.  Use any value that won't be present in the hidelist.

//Go through the hidelist array and look for matches in the guess array.  Anytime a value matches,
//regardless of location, count it as an imperfect match and mark it so it won't get counted again.

//Return the number of imperfect matches
//Hint: you will need a nested for loop.
int ImperfectMatches(int hidelist[], int guess[], int length) {
    int hidelist_copy[length], guess_copy[length], i, j, num_match1 = 0;

    //create copies of the arrays for modification
    copyArray(hidelist_copy, hidelist, length);
    copyArray(guess_copy, guess, length);

    //remove perfect matches from the count
    for (i=0; i<length; i++)
        if (guess_copy[i] == hidelist_copy[i]){
            guess_copy[i] = -5;
            hidelist_copy[i] = -9;
        }

    //determine the number of imperfect matches
    for (i=0; i<length; i++)
        for (j=0; j<length; j++)
            if (guess_copy[i] == hidelist_copy[j]){
                num_match1++;
                hidelist_copy[j] = -7;
                guess_copy [i] = -3;
            }

    return num_match1;

}

//Pre-conditions:  dest and source are integer arrays of size length
//                 source represents a source array: an array to be copied
//                 dest represents a destination array: the location of the copy
//Post-conditions: dest will contain a copy of source

//What to do in this function: traverse the source array and copy each element into
//the corresponding location of the destination array
void copyArray(int dest[], int source[], int length) {

    int i;

    //copies the sources array to the destination array
    for (i=0; i<length; i++)
        dest[i] = source[i];

    return;

}
