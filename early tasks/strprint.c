#include <stdio.h>

int main(void){
    char string[10] = "Hello!";
    for (int i = 0; string[i] != '\0'; i++){
        printf("%c", string[i]);
    }
}