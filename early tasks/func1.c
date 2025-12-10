#include <stdio.h>

int printer(char string[10]){
    for (int i = 0; string[i] != '\0'; i++){
        printf("%c", string[i]);
    }
    printf("\n");
    return 0;
}



int repeater(void){
    static int repeats = 0;
    repeats += 1;
    printf("%d", repeats);
    return 0;
}

int main(void){
    char string[11] = "The Phrase";
    printer(string);
    for (int i = 0; i < 10; i++){
        repeater();
    }
    return 0;
}

// Output of code: Variable i (6, 7, 8, 9) is bigger than j (4, 3, 2, 1), Error because j is out of scope