#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define ARENA_SIZE 64
#define ARENA_ALLOC_TYPE(arena, type) (type*)arena_alloc(arena, sizeof(type), _Alignof(type))
typedef struct Arena {
    void* base;
    void* current;
    void* end;
} Arena;


void arena_init(Arena* arena) {
    arena->base = malloc(ARENA_SIZE);
    arena->current = arena->base;
    arena->end = arena->base + ARENA_SIZE;
    assert(arena->base != NULL);
}

void arena_reset(Arena* arena) {
    printf("\n\nResetting arena...\n");
    arena->current = arena->base;
}

void* arena_alloc(Arena* arena, size_t size, size_t alignment) {
    assert(alignment != 0);
    assert((alignment & (alignment - 1)) == 0);
    uintptr_t current_addr = (uintptr_t)(arena->current);
    uintptr_t aligned_addr = (current_addr + alignment - 1) & ~(alignment - 1);
    size_t padding = aligned_addr - current_addr;

    printf("Pointer after alignment: %zu\n",(size_t)(aligned_addr - (uintptr_t)arena->base));
    printf("Allocating %zu bytes from arena...\n", size);
    assert(arena->current + padding + size <= arena->end);

    arena->current += padding;
    void* ptr = arena->current;
    arena->current += size;

    printf("Successfully allocated %zu bytes. New arena size left: %zu bytes\n", size, arena->end - arena->current);
    printf("Current base address: %p\n", arena->base);

    return ptr;
}

void initialise_variables(Arena* arena){
    int* integer = ARENA_ALLOC_TYPE(arena, int);
    char* character = ARENA_ALLOC_TYPE(arena, char);
    float* float_num = ARENA_ALLOC_TYPE(arena, float);
    double* double_num = ARENA_ALLOC_TYPE(arena, double);

    printf("Integer pointer: %p\n", integer);
    *(int*)integer = 4;
    printf("Integer value: %d\n", *(int*)integer);

    Arena* another_alloc = ARENA_ALLOC_TYPE(arena, struct Arena);
    printf("Struct pointer: %p\n", another_alloc);
}

int main(void){
    Arena arena;
    arena_init(&arena);
    initialise_variables(&arena);
    arena_reset(&arena);
    initialise_variables(&arena);
    arena_reset(&arena);
    free(arena.base);
    return 0;
}