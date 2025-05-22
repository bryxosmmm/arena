#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *buffer;
    size_t capacity;
    size_t offset;
} Arena;

Arena arena_create(size_t size) {
    Arena arena;
    arena.buffer = malloc(size);
    arena.capacity = size;
    arena.offset = 0;
    return arena;
}

void* arena_malloc(Arena* arena, size_t size) {
    size = (size + 7) & ~7;
    if (arena->offset+size > arena->capacity) {
        return NULL;
    }
    void *ptr = arena->buffer + arena->offset;
    arena->offset += size;

    return ptr;
}

void arena_destroy(Arena* arena) {
    free(arena->buffer);
    arena->buffer = NULL;
    arena->capacity = 0;
    arena->offset = 0;
}

void arena_reset(Arena* arena) {
    arena->offset = 0;
}
