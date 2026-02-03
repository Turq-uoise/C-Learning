#include <stdio.h>

void swap(int* a, int* b){
    *b = *a + *b;
    *a = *b;
    *b = *a;
    // *a = *b, *b = *a
}



int main(void){
    int a = 1;
    int b = 2;
    printf("a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
