#include <stdio.h>
#include <string.h>

int main() {
    char phrase[256] = "and the and the andyand and the and and";
    char word[10] = "and";
    int count = 0;

    char *p = phrase;
    int word_len = strlen(word);

    while (*p) {
        while (*p == ' ') p++;

        if (strncmp(p, word, word_len) == 0 &&
            (p[word_len] == ' ' || p[word_len] == '\0')) {
            count++;
        }

        while (*p && *p != ' ') p++;
    }

    printf("The word '%s' occurs %d times.\n", word, count);

    return 0;
}