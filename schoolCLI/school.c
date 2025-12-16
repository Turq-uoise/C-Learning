#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    ENGLISH,
    MATHS,
    HISTORY,
    GEOGRAPHY,
    SCIENCE
} SUBJECT;

const char* subjectNames[] = {
    "English", "Maths", "History", "Geography", "Science"
};

typedef enum {
    A, B, C, D, E, U, NA
} GRADE;

const char* grades[] = {
    "A", "B", "C", "D", "E", "U"
};

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
// Bonus 5) Find students who are taught by given teacher, i.e taught by subject
// Run 1) -> Run 2)

typedef struct SubjectList {
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
    SubjectList* subjects;
    struct Students* next;
} Students;

/* ---------- Teachers ---------- */

Teachers* create_Teachers(char name[30], SUBJECT subject)
{
    Teachers* new_Teachers = malloc(sizeof(Teachers));
    if (!new_Teachers) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    strcpy(new_Teachers->name, name);
    new_Teachers->subject = subject;
    new_Teachers->next = NULL;

    return new_Teachers;
}

void push_front(Teachers** head, char name[30], SUBJECT subject)
{
    Teachers* new_Teachers = create_Teachers(name, subject);
    new_Teachers->next = *head;
    *head = new_Teachers;
}

void add_teacher(Teachers** head, char name[30], SUBJECT subject)
{
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

/* ---------- Students ---------- */

Students* create_student(const char name[30])
{
    Students* new_student = malloc(sizeof(Students));
    if (!new_student) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    strcpy(new_student->name, name);
    new_student->subjects = NULL;
    new_student->next = NULL;

    return new_student;
}

void add_student(Students** head, Students* new_student)
{
    if (*head == NULL) {
        *head = new_student;
        return;
    }

    Students* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = new_student;
}

void add_subject(Students* student, SUBJECT subject, GRADE grade)
{
    SubjectList* node = malloc(sizeof(SubjectList));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    node->subject = subject;
    node->grade = grade;
    node->next = student->subjects;
    student->subjects = node;
}

void input_student_data(Students* student)
{
    int count, subj, grade;

    printf("How many subjects for %s? ", student->name);
    scanf("%d", &count);

    for (int i = 0; i < count; i++) {
        printf("\n0.English 1.Maths 2.History 3.Geography 4.Science\n");
        printf("Choose subject: ");
        scanf("%d", &subj);

        printf("Grade (0=A 1=B 2=C 3=D 4=E 5=U): ");
        scanf("%d", &grade);

        add_subject(student, (SUBJECT)subj, (GRADE)grade);
    }
}

/* ---------- Searching ---------- */

bool search(Teachers* head, char name[30])
{
    Teachers* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0)
            return true;
        curr = curr->next;
    }
    return false;
}

Teachers* search_teachers_by_subject(Teachers* head, SUBJECT subject)
{
    Teachers* result_head = NULL;
    Teachers* result_tail = NULL;

    Teachers* curr = head;
    while (curr != NULL) {
        if (curr->subject == subject) {
            // Create a new node pointing to the same teacher data
            Teachers* node = malloc(sizeof(Teachers));
            if (!node) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }

            strcpy(node->name, curr->name);
            node->subject = curr->subject;
            node->next = NULL;

            // Append to result list
            if (result_head == NULL) {
                result_head = node;
                result_tail = node;
            } else {
                result_tail->next = node;
                result_tail = node;
            }
        }
        curr = curr->next;
    }

    return result_head;
}

bool student_has_subject(const Students* student, SUBJECT subject)
{
    SubjectList* curr = student->subjects;
    while (curr != NULL) {
        if (curr->subject == subject)
            return true;
        curr = curr->next;
    }
    return false;
}

Students* search_students_by_subject_list(Students* head, SUBJECT subject)
{
    Students* result_head = NULL;
    Students* result_tail = NULL;

    Students* curr = head;
    while (curr != NULL) {
        if (student_has_subject(curr, subject)) {
            Students* node = malloc(sizeof(Students));
            if (!node) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }

            strcpy(node->name, curr->name);
            node->subjects = curr->subjects;
            node->next = NULL;

            if (result_head == NULL) {
                result_head = node;
                result_tail = node;
            } else {
                result_tail->next = node;
                result_tail = node;
            }
        }
        curr = curr->next;
    }

    return result_head;
}

Students* get_student_by_name(Students* head, char name[30]){
    Students* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }

    return NULL;
}

GRADE get_student_grade_by_subject(Students* head, char name[30], SUBJECT subject)
{
    GRADE grade = A;
    Students* student = get_student_by_name(head, name);
    if (!student_has_subject(student, subject)){
        printf("Student does not study %s", subjectNames[subject]);
        return NA;
    }

    SubjectList* curr = student->subjects;
    return grade;
}

/* ---------- Printing ---------- */

void print_teacher_list(Teachers* head)
{
    Teachers* curr = head;
    printf("[\n");
    while (curr != NULL) {
        printf("%s teaches %s\n",
               curr->name,
               subjectNames[curr->subject]);
        curr = curr->next;
    }
    printf("]\n");
}


void print_student(const Students* student)
{
    printf("\nStudent: %s\n", student->name);
    printf("Subjects:\n");

    SubjectList* curr = student->subjects;
    while (curr != NULL) {
        printf("  %s : %s\n",
               subjectNames[curr->subject],
               grades[curr->grade]);
        curr = curr->next;
    }
}

void print_student_list(Students* head)
{
    Students* curr = head;
    printf("[\n");
    while (curr != NULL) {
        print_student(curr);
        curr = curr->next;
    }
    printf("]\n");
}

/* ---------- Free ---------- */

void free_list(Teachers** head)
{
    Teachers* curr = *head;
    while (curr != NULL) {
        Teachers* next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}


void free_subjects(SubjectList* head)
{
    while (head != NULL) {
        SubjectList* next = head->next;
        free(head);
        head = next;
    }
}

void free_students(Students** head)
{
    Students* curr = *head;

    while (curr != NULL) {
        Students* next = curr->next;

        free_subjects(curr->subjects);  // free inner list
        free(curr);                     // free student node

        curr = next;
    }

    *head = NULL;
}

void free_student_list_temp(Students* head)
{
    Students* curr = head;
    while (curr != NULL) {
        Students* next = curr->next;
        free(curr);  // only free the node, not the SubjectList
        curr = next;
    }
}

void free_teacher_list_temp(Teachers* head)
{
    Teachers* curr = head;
    while (curr != NULL) {
        Teachers* next = curr->next;
        free(curr);
        curr = next;
    }
}

/* ---------- Main ---------- */

int main(void)
{
    Teachers* teacher_list = NULL;
    Students* student_list = NULL;

    // Auto Create Teachers
    add_teacher(&teacher_list, "William", ENGLISH);
    add_teacher(&teacher_list, "David", HISTORY);
    add_teacher(&teacher_list, "Terrence", MATHS);
    //

    char choice;
    printf("Enter Students Manually? Y/N: ");
    scanf(" %c", &choice);
    choice = toupper(choice);

    if (choice == 'Y') {
        char cont = 'Y';
        printf("Manual Entry: \n");

        while (cont == 'Y') {
            char name[30];

            printf("Enter student name: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            Students* s = create_student(name);
            add_student(&student_list, s);
            input_student_data(s);

            printf("Continue Entering Students? Y/N: ");
            scanf(" %c", &cont); 
            cont = toupper(cont);
        }
    }
    else {
        // Auto Create Students
        Students* s = create_student("John");
        Students* a = create_student("James");
        Students* b = create_student("Simon");

        add_student(&student_list, s);
        add_student(&student_list, a);
        add_student(&student_list, b);

        add_subject(s, ENGLISH, B);
        add_subject(a, ENGLISH, A);
        add_subject(a, MATHS, B);
        add_subject(b, HISTORY, U);
        add_subject(b, GEOGRAPHY, D);
        //
    }

    GRADE john_grade_in_english = get_student_grade_by_subject(student_list, "John", ENGLISH);
    printf("John got %s in %s!\n", grades[john_grade_in_english], subjectNames[ENGLISH]);

    Students* english_students = search_students_by_subject_list(student_list, ENGLISH);
    printf("Students who study English: \n");
    print_student_list(english_students);

    Teachers* math_teachers = search_teachers_by_subject(teacher_list, MATHS);
    printf("Teachers who teach Maths: \n");
    print_teacher_list(math_teachers);

    free_teacher_list_temp(math_teachers);
    free_student_list_temp(english_students);
    free_students(&student_list);
    free_list(&teacher_list);
    return 0;
}
