#include <stdio.h>

int main(void){
    int A = 0;
    int B = 0;
    for (int i = 0; i < 20; i++){
        A += 3;
        B += 7;
        if (A%2 == 1){
            printf("A is odd: %d\n", A);
        }
        if (B%2 == 0){
            printf("B is even: %d\n", B);
        }
        if (i%5 == 0){
            printf("A and B: %d, %d\n", A, B);
        }
    }
    printf("A and B: %d, %d", A, B);

    return 0;
}

// Output of example code: A > B
// A > C
// C > B
// A is unsigned so it is 10 less than the maximum int (2147483647)