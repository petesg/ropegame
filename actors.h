#ifndef ACTORS_H
#define ACTORS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>

#include "errors.h"
#include "draw.h"

typedef struct ACTOR Actor;

struct ACTOR {
    uint32_t pos[2];
    double v[2];
    ALLEGRO_BITMAP* sprite; // TODO figure out how to store sprites
    uint8_t frameIndex;
    void (*initRoutine)(Actor*);
    void (*serviceRoutine)(Actor*);
    void (*disposeRoutine)(Actor*);
};

extern Actor* actors;
extern int numActors;

void initActors(void);
Actor* addActor(void (*newInitRoutine)(Actor*));

void disposeActors(void);

void initGuy(Actor* self);
void serviceGuy(Actor* self);
void disposeGuy(Actor* self);

#endif // ACTORS_H
