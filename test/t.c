#include <stdio.h>

struct S {
    int d;
    char c;
};

int main() {
    int* ip = &((struct S*)0)->d;
    char* cp = &((struct S*)0)->c;
    printf("offset of int: %p\n", ip);
    printf("offset of char: %p\n", cp);
    return 0;
}
