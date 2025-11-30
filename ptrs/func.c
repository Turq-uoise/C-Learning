#include <stdio.h>

void func0(void) { printf("Function 0 called\n"); }
void func1(void) { printf("Function 1 called\n"); }
void func2(void) { printf("Function 2 called\n"); }


void (*table[3])(void) = {func0, func1, func2};


void (*get_function(int index))(void) {
    if (index < 0 || index >= 3) {
        return NULL;
    }
    return table[index];
}

int main(void) {
    for (int i = 0; i < 3; i++) {
        void (*f)(void) = get_function(i);
        if (f != NULL) {
            f();
        }
    }


    return 0;
}
