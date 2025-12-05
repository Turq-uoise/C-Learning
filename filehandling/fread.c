#include <stdio.h>
#include <string.h>

int main() {
    FILE* fptr;

    // Declare the character array 
    // for the data to be read from file
    char data[50];
    fptr = fopen("file.txt", "r");

    if (fptr == NULL) {
        printf("file.txt file failed to open.");
    }
    else {

        printf("The file is now opened.\n");

        // Read the data from the file
        // using fgets() method
        while (fgets(data, 50, fptr)
               != NULL) {

            // Print the data
            printf("File Data: %s", data);
        }

        int spaces = 0;
        for (int i = 0; i <= strlen(data); i++){
            if (data[i] == ' '){
                spaces++;
            }
        }
        spaces++;
        printf("Number of words: %d\n", spaces);

        // Closing the file using fclose()
        fclose(fptr);
    }
    return 0;
}