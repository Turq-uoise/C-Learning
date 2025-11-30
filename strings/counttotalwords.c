#include <stdio.h>
#include <string.h>

int main(void){
    char string[40] = "The Phrase With Words And Such";

    int spaces = 0;
    for (int i = 0; i <= strlen(string); i++){
        if (string[i] == ' '){
            spaces++;
        }
    }
    spaces++;
    printf("%d", spaces);
    
    return 0;
}