/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: c_tut
* Date: 01/30/19
**/
#include <stdio.h>

void swapIntegers(int *, int *);

void swapStrings(char **, char **);

int main(void) {
    int num1 = 5, num2 = 10;

    printf("Before the swap: num1 = %d and num2 = %d\n", num1, num2);
    swapIntegers(&num1, &num2);
    printf("After the swap: num1 = %d and num2 = %d\n", num1, num2);

    char* str1 = "I am string 1";
    char* str2 = "Fuck you string 1 I'm string 2";
    printf("Before the swap: str1 = %s and str2 = %s\n", str1, str2);
    swapStrings(&str1, &str2);
    printf("After the swap: str1 = %s and str2 = %s\n", str1, str2);
    return 0;
}

void swapIntegers(int *n1, int *n2) { /* passed and returned by using values of pointers */
    int temp;

    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

void swapStrings(char **n1, char **n2) {
    char* temp;
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
