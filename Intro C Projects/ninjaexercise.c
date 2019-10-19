/*
Cody Oliver (UCF ID 3125452)
COP 3223 - 0R06
Assignment #3 - Ninja Exercises
9/15/2018
*/
// This program will allow a ninja to train and determine if they have had enough training


// Included libraries
#include <stdio.h>

// Main function

int main() {

// Variable Declaration

    int type, calisth = 0, rope_dist, total_dist = 0;

 //print menu for the user and ask for first exercise
    printf("Ninja Calisthenics:\n");
    printf("\t1 - Practice Kung Fu\n");
    printf("\t2 - Practice Bojutsu\n");
    printf("\t3 - Practice Rope Climbing\n");
    printf("\t4 - Stop training for the day\n\n");
    printf("Choose your exercise!\n");

    scanf("%d", &type);

    //continue until the user enters 4 for quit
    while (type != 4) {

        switch (type) {
            //Kung Fu case
            case 1:
                printf("You go to the dojo and practice your Kung Fu!\n");
                calisth += 1;
                printf("You have done %d calisthenics and %d distance in rope climbing\n\n", calisth, total_dist);
                break;
            //Bojutsu case
            case 2:
                printf("You go to the courtyard and practice your Bojutsu!\n");
                calisth += 1;
                printf("You have done %d calisthenics and %d distance in rope climbing\n\n", calisth, total_dist);
                break;
            //Rope Climbing case
            case 3:
                printf("You go to the rope climbing equipment inside the dojo.\n");
                printf("How much distance did you cover?\n");
                scanf("%d", &rope_dist);
                total_dist += rope_dist;
                printf("You have done %d calisthenics and %d distance in rope climbing\n\n", calisth, total_dist);
                break;
            case 4:
                break;
            default:
                printf("Sorry, that was not a valid option.\n\n");
                break;
        }//end switch

        //reprint menu
        printf("Ninja Calisthenics:\n");
        printf("\t1 - Practice Kung Fu\n");
        printf("\t2 - Practice Bojutsu\n");
        printf("\t3 - Practice Rope Climbing\n");
        printf("\t4 - Stop training for the day\n\n");
        printf("Choose your exercise!\n");

        scanf("%d", &type);

    }//end of while loop

    printf("You have done %d calisthenics and %d distance in rope climbing\n\n", calisth, total_dist);

     //Check if they have trained enough

    if (calisth > 0 && total_dist > 0)
        printf("You are on the path to being a ninja!\n");
    else
        printf("You will need to train more if you want to be a ninja!\n");

    return 0;


}
