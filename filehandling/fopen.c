#include <stdio.h>
#include <stdlib.h>


int main(void) {
    
    // File pointer
    FILE* fptr;

    // Creating file using fopen()
    // with access mode "w"
    fptr = fopen("file.txt", "w");

    // checking if the file is created
    if (fptr == NULL) 
        printf("The file is not opened.");
    else 
        printf("The file is created Successfully.\n");
        fputs("Rahim Mahmood is da best\n", fptr);
        fclose(fptr);
        printf("Data successfully written in file "
               "file.txt\n");
        printf("The file is now closed.\n");
    return 0;
}