/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: c_tut
* Date: 01/23/19
**/
#include <stdio.h>
#include <ctype.h>

#define DANGER_LEVEL 5    /* C Preprocessor -
			- substitution on appearance */

/* like Java ‘final’ */
int main(void) {
    char level;

    puts("Enter the fuel status (\"f\" for \"full\", \"e\" for \"empty\", and \"h\" for \"half full\")!");
    level = (char) tolower(getchar());
    switch (level) {
        case 'f':
            puts("You full");
            break;

        case 'h':
            puts("Its half");
            break;

        case 'e':
            puts("Its empty");
            break;

        default:
            puts("you dumb");
            break;
    }

    return 0;
}
