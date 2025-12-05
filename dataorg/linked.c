#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

Linked* create_Linked(int data) {
    Linked* new_Linked = (Linked*)malloc(sizeof(Linked));
    if (!new_Linked) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_Linked->data = data;
    new_Linked->next = NULL;
    return new_Linked;
}

void push_front(Linked** head, int data) {
    Linked* new_Linked = create_Linked(data);
    new_Linked->next = *head;
    *head = new_Linked;
}

void push_back(Linked** head, int data) {
    Linked* new_Linked = create_Linked(data);

    if (*head == NULL) {
        *head = new_Linked;
        return;
    }

    Linked* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_Linked;
}

bool delete_value(Linked** head, int value) {
    if (*head == NULL) return false;

    Linked* curr = *head;
    Linked* prev = NULL;

    // If deleting head
    if (curr->data == value) {
        *head = curr->next;
        free(curr);
        return true;
    }

    while (curr != NULL && curr->data != value) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) return false;

    prev->next = curr->next;
    free(curr);
    return true;
}

bool search(Linked* head, int value) {
    Linked* curr = head;
    while (curr != NULL) {
        if (curr->data == value) return true;
        curr = curr->next;
    }
    return false;
}

void print_list(Linked* head) {
    Linked* curr = head;
    printf("[ ");
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]\n");
}

void free_list(Linked** head) {
    Linked* curr = *head;
    while (curr != NULL) {
        Linked* next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}
