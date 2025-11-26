#include <stdio.h>

struct A{
    int x;
    double y;
};

int main(void){
    struct A a;
    a.x = 10;
    a.y = 2.0;
    printf("%i\n", a.x);
    printf("%f", a.y);
}