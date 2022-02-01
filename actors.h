#ifndef ACTORS_H
#define ACTORS_H

#include <stdio.h>
#include <stdint.h>

typedef union {
    int32_t pos[2];
    struct {
        int32_t x;
        int32_t y;
    };
} position;

typedef struct {
    position pos;
    void (*initRoutine)(void);
    void (*serviceRoutine)(void);
} actor;

void initActors(void);

#endif // ACTORS_H
