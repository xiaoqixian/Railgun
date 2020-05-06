#include <stdio.h>


struct S {
    int d;
};

int main() {
    int d = ({
            int a = 4, b = 2;
            a - b;
            });
    printf("%d\n", d);
    return 0;
}
