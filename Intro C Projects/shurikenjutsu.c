/*
Cody Oliver (UCF ID 3125452)
COP 3223 - 0R06
Assignment #5 -Shurikenjutsu Competition
10/14/2018
*/
// This program will tally the scores of the Shurikenjutsu Competition to determine who moves on to the next round

// Included libraries
#include <stdio.h>

// Main function

int main() {

// Variable Declaration

    int i, j, set_score_a, set_score_b, total_score_a = 0, total_score_b = 0, num_set, throw_a, throw_b;
    char filename[20];


//Ask for the file name
    printf("What is the name of the input file?\n");
    scanf("%s", &filename);

//Declare, initialize and open the file
    FILE * ifp;
    ifp = fopen(filename, "r");

//Determine the number of sets
    fscanf(ifp, "%d", &num_set);

//Run the competition while tallying scores
    for (i = 1; i <= num_set; i++){

        //determine student 1 set score
        set_score_a = 0;
        for (j = 0; j < 3; j++){
            fscanf(ifp, "%d", &throw_a);
            set_score_a += throw_a;
        }
        //determine student 2 set score
        set_score_b = 0;
        for (j = 0; j < 3; j++){
            fscanf(ifp, "%d", &throw_b);
            set_score_b += throw_b;
        }

        //Print out set scores and add to total score
        printf("\nSet #%d\n", i);
        printf("Student 1: %d points\n", set_score_a);
        printf("Student 2: %d points\n", set_score_b);
        total_score_a += set_score_a;
        total_score_b += set_score_b;
    }

    //Print out final score
    printf("\nFinal Scores\n");
    printf("Student 1: %d points\n", total_score_a);
    printf("Student 2: %d points\n\n", total_score_b);

    //Determine who will move to the next round
    if (total_score_a > total_score_b)
        printf("Student 1 will be advancing to the next round!\n");
    else if (total_score_a < total_score_b)
        printf("Student 2 will be advancing to the next round!\n");
    else
        printf("There has been a tie!");

    //Close file
    fclose(ifp);


return 0;

}
