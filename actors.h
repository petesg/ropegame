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
    void (*serviceRoutine)(void);
} actor;

void initActors(void);
