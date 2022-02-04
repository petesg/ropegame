#ifndef ACTORS_H
#define ACTORS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>

#include "errors.h"
#include "draw.h"

/*typedef union {
    int32_t components[2];
    struct {
        int32_t x;
        int32_t y;
    } coords;
} vector;

typedef struct {
    vector pos;
    ALLEGRO_BITMAP* sprite; // TODO figure out how to store sprites
    void (*initRoutine)(struct actor);
    void (*serviceRoutine)(struct actor);
    void (*drawRoutine)(struct actor); // is this necessary?
    void (*disposeRoutine)(struct actor);
} actor;

typedef void (*actorMember)(actor);

typedef struct {
    int x;
    void (*func)(bullshit);
} bullshit;
void bsfunc(bullshit bs);*/

extern struct actor* actors;
extern uint16_t numActors;

void initActors(void);
struct actor* addActor(void);

void initGuy(struct actor self);
void serviceGuy(struct actor self);
void disposeGuy(struct actor self);

#endif // ACTORS_H
