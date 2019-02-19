/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: Lab 3
* Date: 02/13/19
**/
#include "person.h"

LIST *head = NULL, *tail = NULL;

void inputPersonalData(PERSON *person) {
    // TODO Implement the function
//    puts("Enter a person with the following format: [name] [age] [height] [birthMonth]/[birthDay]/[birthYear]");
//    scanf("%40s %d %f %d/%d/%d", person->name, &person->age, &person->height, &person->bday.month, &person->bday.day, &person->bday.year);
    puts("Enter the next person's name:");
    scanf("%40s", person->name);
    puts("Enter their age:");
    scanf("%d", &person->age);
    puts("Enter their height");
    scanf("%f", &person->height);
    puts("Enter their date of birth (MM/DD/YYYY)");
    scanf("%d/%d/%d", &person->bday.month, &person->bday.day, &person->bday.year);
}

void addPersonalDataToDatabase(PERSON *person) {
    // TODO Implement the function - done
    add(&head, &tail, person);
}

void displayDatabase() {
    // TODO Implement the function - done
    if(head == NULL) {
        return;
    }
    LIST *curNode = head;
    while(curNode != NULL) {
        displayPerson(curNode->data);
        curNode = curNode->next;
    }
}

void displayPerson(PERSON *person) {
    // TODO Implement the function - done
    printf("%s %d %.1f %d/%d/%d\n", person->name, person->age, person->height, person->bday.month, person->bday.day, person->bday.year);
}

PERSON *findPersonInDatabase(char *name) {
    // TODO Implement the function - done
    if(head == NULL) {
        return NULL;
    }
    LIST *curNode = head;
    while(curNode != NULL) {
        PERSON *data = (PERSON *) curNode->data;
        if(strcmp(data->name, name) == 0) {
            return data;
        }
        curNode = curNode->next;
    }
    return NULL; // if not found
}

void removePersonFromDatabase(char *name) {
    // TODO Implement the function - done
    PERSON *toRemove = findPersonInDatabase(name);
    if(toRemove != NULL) {
        delete(&head, &tail, toRemove);
    }
}

void clearDatabase() {
    // TODO Implement the function - done
    clearRecursively(&head, &tail);
}
