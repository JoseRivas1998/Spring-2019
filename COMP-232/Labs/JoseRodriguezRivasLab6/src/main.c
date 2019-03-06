#include "eval.h"

int main(void)
{
    NODE *fullProgram = program();
    printf("Done parsing...\n");
    printProgram(fullProgram);

    exit(0);
}