#include <stdio.h>

int main(void) {
    int i, j, count;
    j = 0;
    i = 0;

    for (j = -3; j<= 3; j++){
        if ((j >= 0) && (i++)){
            printf("%d, %d\n", i, j);
        }
    }

    int y = 0;
    ++y;
    printf("%d", y);
    return 0;
}