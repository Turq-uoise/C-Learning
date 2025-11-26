#include <stdio.h>

typedef struct{
    u_int16_t type: 6;
    u_int16_t priority: 3;
    u_int16_t ID: 7;
} bitfield;

int main(void) {
    unsigned int Prot = 0xB7B2;

    // Map the 16-bit value directly into the struct
    bitfield *fields = (bitfield *)&Prot;

    printf("Type: %u\n", fields->type);
    printf("Priority: %u\n", fields->priority);
    printf("ID: %u\n", fields->ID);

    return 0;
}