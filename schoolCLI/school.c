#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum SUBJECT {
    ENGLISH,
    MATHS,
    HISTORY,
    GEOGRAPHY,
    SCIENCE
};

const char* subjectNames[] = {"English", "Maths", "History", "Geography", "Science"};

typedef struct Teachers {
    char name[30];
    enum SUBJECT subject;
    struct Teachers* next;
} Teachers;

typedef struct Students {
    int data;
    struct Students* next;
} Students;

Teachers* create_Teachers(char name[30], enum SUBJECT subject) {
    Teachers* new_Teachers = (Teachers*)malloc(sizeof(Teachers));
    if (!new_Teachers) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    new_Teachers->subject = subject;
    strcpy(new_Teachers->name, name);
    new_Teachers->next = NULL;
    return new_Teachers;
}

void push_front(Teachers** head, char name[30], enum SUBJECT subject) {
    Teachers* new_Teachers = create_Teachers(name, subject);
    new_Teachers->next = *head;
    *head = new_Teachers;
}

void add_teacher(Teachers** head, char name[30], enum SUBJECT subject) {
    Teachers* new_Teachers = create_Teachers(name, subject);

    if (*head == NULL) {
        *head = new_Teachers;
        return;
    }

    Teachers* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = new_Teachers;
}

bool delete_value(Teachers** head, char name[30]) {
    if (*head == NULL) return false;

    Teachers* curr = *head;
    Teachers* prev = NULL;

    if (strcmp(curr->name, name) != 0) {
        *head = curr->next;
        free(curr);
        return true;
    }

    while (curr != NULL && strcmp(curr->name, name) == 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) return false;

    prev->next = curr->next;
    free(curr);
    return true;
}

bool search(Teachers* head, char name[30]) {
    Teachers* curr = head;
    while (curr != NULL) {
        if (curr->name == name) return true;
        curr = curr->next;
    }
    return false;
}

void print_list(Teachers* head) {
    Teachers* curr = head;
    printf("[ \n");
    while (curr != NULL) {
        printf("%s teaches %s \n", curr->name, subjectNames[curr->subject]);
        curr = curr->next;
    }
    printf("]\n");
}

void free_list(Teachers** head) {
    Teachers* curr = *head;
    while (curr != NULL) {
        Teachers* next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}



int main() {
    Teachers* teacher_list = NULL;
    add_teacher(&teacher_list, "Ayesha", ENGLISH);
    add_teacher(&teacher_list, "Arthur", HISTORY);
    add_teacher(&teacher_list, "Terrence", MATHS);
    print_list(teacher_list);
    return 0;
}