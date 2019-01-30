/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: c_tut
* Date: 01/30/19
**/

#ifndef C_TUT_PERSON_H
#define C_TUT_PERSON_H

typedef char NAME[41];

typedef struct date {
    int month;
    int day;
    int year;
} DATE;

typedef struct person {
    NAME name;
    int age;
    float height;
    DATE bday;
} PERSON;

void addEmployee(PERSON *employee);
void displayAllEmployees(PERSON employees[], int numberOfEmployees);
void displayEmployee(PERSON *employee);

#endif //C_TUT_PERSON_H
