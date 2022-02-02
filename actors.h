#ifndef ACTORS_H
#define ACTORS_H

#include <stdio.h>
#include <stdint-gcc.h>

typedef union {
    int32_t components[2];
    struct {
        int32_t x;
        int32_t y;
    } coords;
} vector;

typedef struct {
    vector pos;
    void *sprite; // TODO figure out how to store sprites
    void (*initRoutine)(void);
    void (*serviceRoutine)(void);
} actor;

void initActors(void);

#endif // ACTORS_H
