#include <stdio.h>
#include "eqlib.h"

int main() {
    int x = 12;

    printf("eq1(%d) = %d\n", x, eq1(x));
    printf("eq2(%d) = %d\n", x, eq2(x));
    printf("eq3(%d) = %d\n", x, eq3(x));

    return 0;
}