#ifndef LINKED_H
#define LINKED_H

#include <stdbool.h>

typedef struct Linked {
    int data;
    struct Linked* next;
} Linked;

Linked* create_linked(int data);

void push_front(Linked** head, int data);
void push_back(Linked** head, int data);

bool delete_value(Linked** head, int value);
bool search(Linked* head, int value);

void print_list(Linked* head);
void free_list(Linked** head);

#endif
