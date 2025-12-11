#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    ENGLISH,
    MATHS,
    HISTORY,
    GEOGRAPHY,
    SCIENCE
} SUBJECT;

const char* subjectNames[] = {"English", "Maths", "History", "Geography", "Science"};

typedef enum {
   A, B, C, D, E, U
} GRADE;

const char* grades[] = {"A", "B", "C", "D", "E", "U"};

// Structure:
// Teacher has name + subject
// Student has list of subjects
// Each subject in list has grade
// Operations:
// 1) Search students by subject: 
// Go through each student in Students list -> Go through subjects they studies -> If subject is present, return student
// 2) Search teacher by subject:
// Search for subject in Teachers list, if it is present then return teacher
// 3) Find grade student got in specific subject:
// Pick student; Pick subject; Return grade
// Bonus; 4) Search for teachers that teach a given student:
// Go through each subject student studies -> Run 2)
// 5) Find students who are taught by given teacher, i.e taught by subject
// Run 1) -> Run 2)

typedef struct SubjectList{
    SUBJECT subject;
    GRADE grade;
    struct SubjectList* next;
} SubjectList;

typedef struct Teachers {
    char name[30];
    SUBJECT subject;
    struct Teachers* next;
} Teachers;

typedef struct Students {
    char name[30];
    SubjectList subjects;
    struct Students* next;
} Students;

Teachers* create_Teachers(char name[30], SUBJECT subject) {
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

void push_front(Teachers** head, char name[30], SUBJECT subject) {
    Teachers* new_Teachers = create_Teachers(name, subject);
    new_Teachers->next = *head;
    *head = new_Teachers;
}

void add_teacher(Teachers** head, char name[30], SUBJECT subject) {
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