#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Structure to represent the doubly linked list
typedef struct Node {
  
  // Data field - can be of any type and count
  int data;
  
  // Pointer to the next node
  struct Node* next;
  
  // Pointer to the previous node
  struct Node* prev;
} Node;

Node* create_Node(int data) {
    Node* new_Node = (Node*)malloc(sizeof(Node));
    if (!new_Node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    new_Node->data = data;
    new_Node->next = NULL;
    return new_Node;
}

void add_station(Node** head, int data) {
    Node* new_Node = create_Node(data);

    if (*head == NULL) {
        *head = new_Node;
        return;
    }

    Node* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_Node;
}

bool close_station(Node** head, int value) {
    if (*head == NULL) return false;

    Node* curr = *head;
    Node* prev = NULL;

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

void print_list(Node* head) {
    Node* curr = head;
    printf("[ ");
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("]\n");
}

int main(void){
    Node* train_line = NULL;

    printf("Appending to list: 1, 2, 3\n");
    add_station(&train_line, 1);
    add_station(&train_line, 2);
    add_station(&train_line, 3);
    print_list(train_line);

    printf("Closing station 2...\n");
    close_station(&train_line, 2);
    print_list(train_line);
    return 0;
}