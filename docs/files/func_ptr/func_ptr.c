#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// ENUM
enum stuff {
    THING1, THING2, THING3, THING4, 
    THING5, THING6, THING7, THING8,
    THING9, THING10, THING11, THING12
};

// DUMMY FUNCTIONS
void someFunc1() {
    printf("Do THING1 things\n");
}

void someFunc2() {
    printf("Do THING2 things\n");
}

void someFunc3() {
    printf("Do THING3 things\n");
}

void someFunc4() {
    printf("Do THING4 things\n");
}

void someFunc5() {
    printf("Do THING5 things\n");
}

void someFunc6() {
    printf("Do THING6 things\n");
}

void someFunc7() {
    printf("Do THING7 things\n");
}

void someFunc8() {
    printf("Do THING8 things\n");
}

void someFunc9() {
    printf("Do THING9 things\n");
}

void someFunc10() {
    printf("Do THING10 things\n");
}

void someFunc11() {
    printf("Do THING11 things\n");
}

void someFunc12() {
    printf("Do THING12 things\n");
}

void (*func_ptr[])() = {
        someFunc1, someFunc2, someFunc3, someFunc4,
        someFunc5, someFunc6, someFunc7, someFunc8,
        someFunc9, someFunc10, someFunc11, someFunc12
    };

int main() {

    enum stuff THING2 = 15;

    func_ptr[THING2]();

    return 0;
}