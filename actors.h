#ifndef ACTORS_H
#define ACTORS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>

#include "structs.h"
#include "errors.h"
#include "draw.h"

extern Actor* actors;
extern int numActors;

void initActors(void);
Actor* addActor(void (*newInitRoutine)(Actor*));
void serviceActors(void);
void disposeActors(void);

void initGuy(Actor* self);
void serviceGuy(Actor* self);
void disposeGuy(Actor* self);

#endif // ACTORS_H
