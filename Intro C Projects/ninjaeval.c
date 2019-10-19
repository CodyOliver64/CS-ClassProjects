/*
Cody Oliver (UCF ID 3125452)
COP 3223 - 0R06
Assignment #2 - Joining the Academy
9/8/2018
*/
// This program will determine whether or not a person is able to train as a ninja


// Included libraries
#include <stdio.h>

// Main function

int main() {

    // Variable Declaration

    char afraid_dark, excercise;
    int mintues_excercise;

    // Prompt User for input information

    printf("Are you afraid of the dark? (Y/N)\n");
    scanf(" %c", &afraid_dark);

    printf("Do you exercise? (Y/N)\n");
    scanf(" %c", &excercise);

    // Ask for amount of time IF they exercise
    if (excercise == 'Y') {
        printf("How many minutes do you exercise per day?\n");
        scanf("%d", &mintues_excercise);
    }

    // Evaluate and output results

    if ((afraid_dark == 'N' && excercise == 'Y') && mintues_excercise >= 10)
        printf("You may begin training as a ninja!\n");

    else
        printf("You may not train as a ninja.\n");



    return 0;


}
