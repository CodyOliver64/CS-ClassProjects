/*
Cody Oliver (UCF ID 3125452)
COP 3223 - 0R06
Assignment #1 - Ninja Rope
9/1/2018
*/
// This program will determine how much rope is needed to scale a Ninja Academy mountain


// Included libraries
#include <stdio.h>
#include <math.h>


int main(){

    //Variable declaration
    int mountain_height, skein_hundred, skein_ten;

    //Prompt user for input information
    printf("How tall is the mountain in feet?\n");
    scanf("%d", &mountain_height);

    //Calculations
    skein_hundred = mountain_height/100;
    skein_ten = ceil(mountain_height % 100/10.0);

    //Output results
    printf("You will need %d skeins of 100 feet rope and %d skeins of 10 feet rope!\n", skein_hundred, skein_ten);


    return 0;
}

