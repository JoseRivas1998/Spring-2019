/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: c_tut
* Date: 01/30/19
**/
#include <stdio.h>
#include "person.h"

void addEmployee(PERSON *employee) {
    printf("Name: ");
    scanf("%s", employee->name);
    printf("Age: ");
    scanf("%d", &employee->age);
    printf("Height: ");
    scanf("%f", &employee->height);
    printf("BDay Month: ");
    scanf("%d", &employee->bday.month);
    printf("BDay Day: ");
    scanf("%d", &employee->bday.day);
    printf("BDay Year: ");
    scanf("%d", &employee->bday.year);
}

void displayAllEmployees(PERSON employees[], int numberOfEmployees) {
    for (int i = 0; i < numberOfEmployees; i++) {
        displayEmployee(&employees[i]);
    }
}

void displayEmployee(PERSON *employee) {
    printf("Name: %s\nAge: %d\nHeight: %f\nBirthday: %d/%d/%d\n\n",
           employee->name, employee->age, employee->height,
           employee->bday.day, employee->bday.month, employee->bday.year
    );
}
