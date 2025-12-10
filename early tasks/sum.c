#include <stdio.h>

int sum (int a, int b, int c){
    return a + b + c;
}


int main(void){
    int a = 5;
    int b = 4;
    int c = 10;
    printf("%d", sum(a, b, c));
    return 0;
}