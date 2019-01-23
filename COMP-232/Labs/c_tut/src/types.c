/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: c_tut
* Date: 01/23/19
**/
#include <stdio.h>

int main(void) {
    int nStudents = 0; /* Initialization, required */
    int nFaculty = 0;

    printf("How many students does CSUCI have ?:");
    scanf("%d", &nStudents);  /* Read input */
//    printf("CSUCI has %d students.\n", nStudents);

    printf("How many faculty?: ");
    scanf("%d", &nFaculty);

    float ratio = (float) nStudents / nFaculty;

    printf("The student to faculty ratio is: %f", ratio);

    return 0;
}
