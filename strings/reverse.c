#include <stdio.h>
#include <string.h>

int main(void){
    char string[11] = "The Phrase";

    for (int i = 0; i <= strlen(string); i++){
        printf("%c", string[strlen(string) - i]);
    }

    return 0;
}