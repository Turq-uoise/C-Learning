#include <stdio.h>
#include <stdlib.h>

int main(void){
    int a = 123;
    char string[10] = "123984";
    char* end;
    long result;

    for (int i = 0; string[i] != '\0'; i++){
        printf("%d", (int)string[i] - '0');
    }
    return 0;
}