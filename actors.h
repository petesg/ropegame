#ifndef ACTORS_H
#define ACTORS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>

#include "errors.h"
#include "draw.h"

typedef struct ACTOR actor;

struct ACTOR {
    uint32_t pos[2];
    double v[2];
    ALLEGRO_BITMAP* sprite; // TODO figure out how to store sprites
    void (*initRoutine)(actor*);
    void (*serviceRoutine)(actor*);
    void (*disposeRoutine)(actor*); // TODO maybe make these take pointers
};

extern actor* actors;
extern int numActors;

void initActors(void);
actor* addActor(void (*newInitRoutine)(actor*));

void disposeActors(void);

void initGuy(actor* self);
void serviceGuy(actor* self);
void disposeGuy(actor* self);

#endif // ACTORS_H
