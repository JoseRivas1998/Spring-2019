/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: c_tut
* Date: 01/23/19
**/
#include <stdio.h>

#define MAX_NUM_OF_CELLS 128

int main(void) {
    double number[MAX_NUM_OF_CELLS];
    double sum = 0;

    int numToProcess = 0;

    puts("Provide a dseired number of doubles?");
    scanf("%d", &numToProcess);

    if(numToProcess > MAX_NUM_OF_CELLS) {
        numToProcess = MAX_NUM_OF_CELLS;
    }

    puts("Provide the doubles?");

    double currentVal = 0;
    for (int index = 0; index < numToProcess; index++) {
        scanf("%lf", &currentVal);
        number[index] = currentVal;
    }

    for (int index = 0; index < numToProcess; index = index + 1) {
        sum += number[index];  /* sum array elements */
    }

    double average = sum / numToProcess;

    printf("Data: ");
    for (int i = 0; i < numToProcess; i++) {
        printf("%0.1lf ", number[i]);
    }
    printf("\n");

    printf("Average: %0.1lf", average);

    return 0;
}
