/*
Cody Oliver (UCF ID 3125452)
COP 3223 - 0R06
Assignment #4 - Ninja Shopping
9/23/2018
*/
// This program will help a ninja shop at various stores while tracking the total of each shopping list and the lowest total of each trip


// Included libraries
#include <stdio.h>

// Main function

int main() {

// Variable Declaration

    int i, j, num_shop, num_ingred, low_store;
    float ingred_price, total, low_total = 0;

//ask how many total shops will be visited
    printf("How many shops will you be visiting?\n");
    scanf("%d", &num_shop);

//shop at each store determining the number of items and price of each
    for (i = 1; i <= num_shop; i++){

        printf("You are at shop #%d.\n", i);
        total = 0;

        //ask how many ingredients are needed
        printf("How many ingredients do you need at shop #%d?\n", i);
        scanf("%d", &num_ingred);

        //ask how much each ingredient is and add it to the shop total
        for (j = 1; j <= num_ingred; j++){

            printf("How much is ingredient #%d?\n", j);
            scanf("%f", &ingred_price);
            total += ingred_price;
        }//end of 2nd for loop

        //print total from current store
        printf("\nYour total at shop #%d is $%.2f.\n\n", i, total);

        //check if this is the lowest shopping bill
        if ((total < low_total) || low_total == 0){

            low_total = total;
            low_store = i;
        }//end of if statement

    }//end of 1st for loop

    //print lowest store and total
    printf("Your cheapest order was at shop #%d and cost $%.2f.\n", low_store, low_total);

return 0;

}
