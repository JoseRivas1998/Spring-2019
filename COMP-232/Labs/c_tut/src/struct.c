#include <stdio.h>
#include <stdlib.h>
#include "person.h"

int main(void) {
    int numEmp;
    printf("Enter how many employees: ");
    scanf("%d", &numEmp);

    PERSON employees[numEmp];

    for (int i = 0; i < numEmp; i++) {
        addEmployee(&employees[i]);
    }

    displayAllEmployees(employees, numEmp);

    return 0;
}
