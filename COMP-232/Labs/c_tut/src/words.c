/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: c_tut
* Date: 01/30/19
**/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_POINTERS 100
#define BUFFER_SIZE 30

int main() {
    char* stringArray[NUM_POINTERS];
    char buffer[BUFFER_SIZE];
    int loopControl = 1;
    size_t chars = 0;
    int strings = 0;
    while (loopControl) {
        scanf("%s", buffer);
        if(strcmp(buffer, "END") == 0) {
            loopControl = 0;
        } else {
            chars = strlen(buffer) + 1;
            stringArray[strings] = malloc(chars * sizeof(char));
            strcpy(stringArray[strings], buffer);
            strings++;
        }
    }
    printf("The following %d words have been read:\n", strings);
    for (int i = 0; i < strings; ++i) {
        printf("%s\n", stringArray[i]);
    }
    return 0;
}