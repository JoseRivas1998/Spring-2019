#include <stdio.h>

/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: c_tut
* Date: 01/30/19
**/
void add(int, int);

void sub(int, int);

void mult(int, int);

void div(int, int);

void calc(void (*)(int, int), int, int);

int main(void) {
    int a;
    int b;
    char operand;
    int loopControl = 1;
    void (*toDo)(int, int);
    while(loopControl) {
        printf("calc> ");
        scanf("%d %c %d", &a, &operand, &b);
        switch (operand) {
            case '+':
                toDo = add;
                break;
            case '-':
                toDo = sub;
                break;
            case '*':
                toDo = mult;
                break;
            case '/':
                toDo = div;
                break;
            default:
                loopControl = 0;
                break;
        }
        if(loopControl) {
            calc(toDo, a, b);
        }
    }
    return 0;
}

void add(int a, int b) {
    printf("%d\n", (a + b));
}

void sub(int a, int b) {
    printf("%d\n", (a - b));
}

void mult(int a, int b) {
    printf("%d\n", (a * b));
}

void div(int a, int b) {
    printf("%d\n", (a / b));
}

void calc(void (*f)(int, int), int a, int b) {
    (*f)(a, b);
}

