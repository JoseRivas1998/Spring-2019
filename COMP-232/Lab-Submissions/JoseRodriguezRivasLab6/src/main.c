/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 6
* Date: 03/07/19
**/
#include <stdio.h>
#include "eval.h"

int main(int argc, char** argv)
{
    freopen(argv[1], "r", stdin);
    NODE *fullProgram = program();
    printf("Done parsing...\n");
    printProgram(fullProgram);
    exit(0);
}