/*
Cody Oliver (UCF ID 3125452)
COP 3223 - 0R06
Assignment #8 - Ninja Final
12/2/2018
*/

//pre-processor directives
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//Declare structures
struct ninja {
    int search;
    int stealth;
};

struct map {
    int searchval;
    int item;
    int found;
};

//Function Prototypes
void getInfo(struct map temple[3][3], struct ninja * team);
void printNinja(int * hours, struct ninja * team);
void printMap(struct map temple[3][3]);
char* moveNinja(int movea, int moveb, struct map temple[3][3], struct ninja * team, int i, int * relic, char * results);
void printResults (int relic);


int main() {

    //Declare Variables
    struct ninja team[4];
    struct map temple[3][3];
    int hours = 2, relic = 0, movea, moveb, i;
    char results [100];

    //populate the map and the ninja team
    printf("You have arrived at the Temple!\n");
    getInfo(temple, team);

    while(hours > 0 && relic != 4){

        //print the hours left and the ninja stats for round 1
        printNinja(&hours, team);

        //loop to get the users input for each ninjas turn
        for(i=0; i<4; i++){
            printf("\nWhere would you like to send Ninja %d\n", i+1);
            //print the updated map after each ninja moves
            printMap(temple);

            scanf("%d", &movea);
            scanf("%d", &moveb);


            //evaluate their move and return the results
            printf("%s", (moveNinja(movea, moveb, temple, team, i, &relic, results)));



        }
    }

    //print the results of the temple run
    printResults(relic);

return 0;

}


//Pre Conditions: The function will take in a 3x3 array of the map and a 1x4 array of the team of ninjas
//Post Conditions: The function will read from a file to input proper attributes to both the map spaces and the ninja skills
void getInfo(struct map temple[3][3], struct ninja * team){

    int i, j;
    char userfile[20];

    //ask user for the name of the file
    printf("What is the name of your map?\n");
    scanf("%s", userfile);

    //open file
    FILE * ifp = fopen(userfile, "r");

    //initialize the map
    for(i=0; i<3; i++)
        for(j=0; j<3; j++){
            fscanf(ifp, "%d", &temple[i][j].searchval);
            fscanf(ifp, "%d", &temple[i][j].item);
            temple[i][j].found = 0;
        }

    //initialize the ninja team
    for(i=0; i<4; i++){
        fscanf(ifp, "%d", &team[i].search);
        fscanf(ifp, "%d", &team[i].stealth);
    }

    //close the file
    fclose(ifp);

    return;
}

//Pre Conditions: The function will take in the starting hours to solve the temple as well as the array of ninjas and their attributes
//Post Conditions: The function will print the current hours left and the ninjas with their attributes as well as decrease the time left by 1 hour
void printNinja (int * hours, struct ninja * team){

    int i;

    //print current hours left
    printf("\nYou have %d hours left to collect the relics.\n", *hours);

    //print ninja stats
    printf("Ninja\tSearch\tStealth\n");
    for(i=0; i<4; i++)
        printf("%d\t%d\t%d\n", i+1, team[i].search,team[i].stealth);

    *hours = *hours - 1;
return;

}

//Pre Conditions: The function will take in the 3x3 map array
//Post Conditions: The function will print the current status of the map, noting its search value, whether its been searched, and what was found there if searched
void printMap (struct map temple[3][3]){
    int i, j;

    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            if(temple[i][j].found == 0)
                printf("%ds\t", temple[i][j].searchval);
            else{
                if(temple[i][j].item == 0)
                    printf("TRAP\t");
                else if(temple[i][j].item == 1)
                    printf("KATANA\t");
                else if(temple[i][j].item == 2)
                    printf("SCROLL\t");
                else if(temple[i][j].item == 3)
                    printf("JADE\t");
                else if(temple[i][j].item == 4)
                    printf("MASK\t");
                else
                    printf("NOTHING\t");
            }
        }
        printf("\n");
    }
return;
}

//Pre Conditions: The function will take in the 3x3 map array, the ninja stats array, the move the user has chosen, the ninja whos turn it is, true/false values for the relics, and an alert string
//Post Conditions: The function will evaluate the result of each ninjas turn depending on where they choose to search. It will determine if they get caught, alert the user of their results, and update the map/relic status/stealth score
char* moveNinja(int movea, int moveb, struct map temple[3][3], struct ninja * team, int i, int * relic, char * results){

    int randnumb;


    //seed the random number generator and generate a random number
    srand(time(0));
    randnumb = rand() % (team[i].stealth + 1);
    //determine if the ninja was caught
    if(randnumb == 0){
        strcpy(results, "\nYour ninja has been caught!\n");
        return results;
    }


    if(team[i].search < temple[movea-1][moveb-1].searchval)
        strcpy(results, "\nYour ninja was not able to search this room.\n");

    //determine if the ninja fell into a trap. If so reduce their stealth, update the map, and alert the user
    else if(temple[movea-1][moveb-1].item == 0){
        strcpy(results, "\nYour ninja fell into a trap!\n");
        team[i].stealth -= 1;
        temple[movea-1][moveb-1].found = 1;
    }

    //determine if the ninja found the KATANA. If so update the map, update KATANA to true, and alert the user of their find.
    else if(temple[movea-1][moveb-1].item == 1){
        strcpy(results, "\nYou have found the founder's KATANA.\n");
        *relic = *relic+1;
        temple[movea-1][moveb-1].found = 1;
    }

    //determine if the ninja found the SCROLL. If so update the map, update SCROLL to true, and alert the user of their find.
    else if(temple[movea-1][moveb-1].item == 2){
        strcpy(results, "\nYou have found an ornate SCROLL.\n");
        *relic = *relic+1;
        temple[movea-1][moveb-1].found = 1;
    }

    //determine if the ninja found the JADE. If so update the map, update JADE to true, and alert the user of their find.
    else if(temple[movea-1][moveb-1].item == 3){
        strcpy(results, "\nYou have found a JADE statue.\n");
        *relic = *relic+1;
        temple[movea-1][moveb-1].found = 1;
    }

    //determine if the ninja found the MASK. If so update the map, update MASK to true, and alert the user of their find.
    else if(temple[movea-1][moveb-1].item == 4){
        strcpy(results, "\nYou have found an ancient MASK.\n");
        *relic = *relic+1;
        temple[movea-1][moveb-1].found = 1;
    }

    //determine if the ninja found NOTHING. If so update the map and alert the user of their find.
    else{
        strcpy(results, "\nThere is nothing in this room!\n");
        temple[movea-1][moveb-1].found = 1;
    }



return results;
}

//Pre Conditions: Takes in the true/false values for each of the relics
//Post Conditions: If they found all relics let them know they won, if not let them know they must leave and how many relics they found
void printResults (int relic){

    if(relic == 4)
        printf("\nYou have retrieved all of the relics!\n");
    else
        printf("\nYou are forced to leave the temple. You retrieved %d relics for the Ninja Academy!\n", relic);

return;
}


