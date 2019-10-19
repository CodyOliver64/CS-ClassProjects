/*
Cody Oliver (UCF ID 3125452)
COP 3223 - 0R06
Assignment #6 - Advancing to Master Class
10/28/2018
*/
// This program will read in the scores from the Ninja Test and allow the user to compare their score and determine various averages of other users. It will also determine if the user can advance.

// Included libraries
#include <stdio.h>

// Main function

int main() {

// Variable Declaration

    int i, j, temp, user_score, header, scores[10000], h_scores[10000], response, low_b, up_b, total, lowest, highest, counter, pass_num, flag;
    float average, percent;
    char filename[20];


//Ask for the file name and the users score
    printf("What is the name of the input file?\n");
    scanf("%s", &filename);

    printf("What did you score on your assessment?\n");
    scanf("%d", &user_score);

//Declare, initialize and open the file
    FILE * ifp;
    ifp = fopen(filename, "r");


//Determine the number of scores, read them into an array and confirm the file has been read
    fscanf(ifp, "%d", &header);

    for(i=0; i < header; i++)
        fscanf(ifp, "%d", &scores[i]);

    printf("The scores for %d students of the Ninja Academy have been read.\n\n", header);

//Print the menu and ask them for their option
    printf("What would you like to do?\n");
    printf("1. Calculate the average assessment score for a subset of the scores.\n");
    printf("2. Calculate the minimum assessment score for a subset of the scores.\n");
    printf("3. Calculate the maximum assessment score for a subset of the scores.\n");
    printf("4. Calculate the number of assessment scores exceeding the user's score.\n");
    printf("5. Calculate what percentage of the assessment scores are under the user's score.\n");
    printf("6. Determine how many other students scored the same as the user.\n");
    printf("7. Determine if the user will be able to advance.\n");
    printf("8. Quit\n");
    scanf("%d", &response);

//Depending on the response, perform each action and reprint the menu at the end
    while(response != 8) {
        switch(response) {
            //average of subset
            case 1:
                printf("What is the lower bound?\n");
                scanf("%d", &low_b);

                printf("What is the upper bound?\n");
                scanf("%d", &up_b);

                total = 0;

                for(i = low_b; i <= up_b; i++)
                    total += scores[i];

                average = (float) total / (up_b - low_b + 1);

                printf("\nThe average score from student %d to student %d is %.2f.\n\n", low_b, up_b, average);

                break;

            //minimum of subset
            case 2:
                printf("What is the lower bound?\n");
                scanf("%d", &low_b);

                printf("What is the upper bound?\n");
                scanf("%d", &up_b);

                lowest = scores[low_b];

                for(i = low_b + 1; i <= up_b; i++)
                    if (scores[i] < lowest)
                        lowest = scores[i];

                printf("\nThe lowest score from student %d to student %d is %d.\n\n", low_b, up_b, lowest);

                break;

            //maximum of subset
            case 3:
                printf("What is the lower bound?\n");
                scanf("%d", &low_b);

                printf("What is the upper bound?\n");
                scanf("%d", &up_b);

                highest = scores[low_b];

                for(i = low_b + 1; i <= up_b; i++)
                    if (scores[i] > highest)
                        highest = scores[i];

                printf("\nThe highest score from student %d to student %d is %d.\n\n", low_b, up_b, highest);

                break;

            //how many students scored higher than the user
            case 4:
                counter = 0;
                for(i = 0; i < header; i++)
                    if (scores[i] > user_score)
                        counter++;

                printf("\n%d students scored higher than you.\n\n", counter);

                break;

            //percent of students who scored lower than the user
            case 5:
                counter = 0;
                for(i = 0; i < header; i++)
                    if (scores[i] < user_score)
                        counter++;

                average = ((float) counter / header) * 100;

                printf("\n%.2f percent of students scored lower than you.\n\n", average);

                break;

            //how many students scored the same
            case 6:
                counter = 0;
                for(i = 0; i < header; i++)
                    if (scores[i] == user_score)
                        counter++;

                printf("\n%d students scored the same as you.\n\n", counter);

                break;

            //determine if user will pass
            case 7:
                //ask how many will pass
                printf("How many students will be advancing?\n");
                scanf("%d", &pass_num);

                //create new score list
                for (i = 0; i < header; i++)
                    h_scores[i] = scores[i];

                //sort the new array, greatest to least
                for (i = 0; i < header; i++)
                    for (int j = 0; j < header; j++)
                        if (h_scores[j] < h_scores[i]){
                            temp = h_scores[i];
                            h_scores[i] = h_scores[j];
                            h_scores[j] = temp;
                        }

                //check if users score is high enough
                flag = 1;
                for (i = 0; i < pass_num; i++)
                    if (user_score >= h_scores[i])
                            flag = 2;

                //tell the user if they passed
                if (flag == 2)
                    printf("\nYou will be able to advance to the master class!\n\n");
                else
                    printf("\nYou will not be able to advance.\n\n");

                break;

            default:
                printf("\nSorry, that was not a valid option.\n\n");
                break;
            }

        //prompt the user for a new option
        printf("What would you like to do?\n");
        printf("1. Calculate the average assessment score for a subset of the scores.\n");
        printf("2. Calculate the minimum assessment score for a subset of the scores.\n");
        printf("3. Calculate the maximum assessment score for a subset of the scores.\n");
        printf("4. Calculate the number of assessment scores exceeding the user's score.\n");
        printf("5. Calculate what percentage of the assessment scores are under the user's score.\n");
        printf("6. Determine how many other students scored the same as the user.\n");
        printf("7. Determine if the user will be able to advance.\n");
        printf("8. Quit\n");
        scanf("%d", &response);
    }


    //Close file
    fclose(ifp);


return 0;

}
