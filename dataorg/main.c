#include <stdio.h>
#include "linked.h"

int main() {
    Linked* list = NULL;

    printf("Pushing to front: 3, 2, 1\n");
    push_front(&list, 3);
    push_front(&list, 2);
    push_front(&list, 1);
    print_list(list);

    printf("Pushing to back: 4, 5\n");
    push_back(&list, 4);
    push_back(&list, 5);
    print_list(list);

    printf("Searching for 3: %s\n", search(list, 3) ? "Found" : "Not Found");
    printf("Searching for 10: %s\n", search(list, 10) ? "Found" : "Not Found");

    printf("Deleting 3...\n");
    delete_value(&list, 3);
    print_list(list);

    printf("Deleting 1 (head)...\n");
    delete_value(&list, 1);
    print_list(list);

    printf("Deleting 5 (tail)...\n");
    delete_value(&list, 5);
    print_list(list);

    free_list(&list);

    return 0;
}
