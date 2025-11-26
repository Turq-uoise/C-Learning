#include <stdio.h>

struct bitfield{
    u_int16_t type: 6;
    u_int16_t priority: 3;
    u_int16_t ID: 7;
};

int main(void) {
    unsigned short Prot = 0xB7B2;

    unsigned short test = 0x02;

    struct bitfield bit;
    Prot = Prot>>bit.type;
    printf("%d\n", Prot);

    // Map the 16-bit value directly into the struct
    //bitfield *fields = (bitfield *)&Prot;

    //printf("Type: %u\n", fields->type);
    //printf("Priority: %u\n", fields->priority);
    //printf("ID: %u\n", fields->ID);
    return 0;
}