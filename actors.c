#include "actors.h"

Actor* actors;      // dynamic array of all actors in game
int numActors = 0;  // size of actors array
Actor* tempActor;   // dummy memory block for setting up new actors or defaulting to when out of memory

void initActors(void) {

    printf("actors init\n");

    // add special actors here
    addActor(initGuy);
    addActor(initGuy)->pos[0] = 1000;

    printf("added guy (%d, %d) - %p\n", actors[0].pos[0], actors[0].pos[1], &actors[0]);

}

Actor* addActor(void (*newInitRoutine)(Actor*)) {
    printf("adding actor to actors[%d]\n", numActors);
    Actor* tempPtr = realloc(actors, sizeof(Actor) * (numActors + 1));
    if (!tempPtr) {
        errorOutOfMemory();
        return tempActor; // TODO figure out how I really want to handle this
    }
    actors = tempPtr;
    printf("array resized (numActors is still [%d])\n", numActors);
    Actor* newActor = actors + numActors++;
    // initialize new actor
    printf("actors: %p, newActor: %p, (actors+1: %p)\n", actors, newActor, actors + 1);
    newActor->initRoutine = newInitRoutine;
    newActor->initRoutine(newActor);
    printf("initialized actor\n");
    return newActor; // doing it this way so there's no need to memcpy from a temp outside of addActor()
}

void initGuy(Actor* self) {
    self->pos[0] = 200;
    self->pos[1] = 200;
    self->serviceRoutine = serviceGuy;
    self->disposeRoutine = disposeGuy;
    self->sprite.sheet = getBitmap(ASSET_SH_GUY);//al_load_bitmap("assets/guy.png"); // TODO make this a spritesheet reference instead of bitmap here
    if(!self->sprite.sheet) {
        // TODO complain
    }
    printf("guy is initialized (%d, %d) - [%p]\n", self->pos[0], self->pos[1], self);
}

void serviceGuy(Actor* self) {

}

void disposeGuy(Actor* self) {
    //al_destroy_bitmap(self->sprite.sheet); // TODO this needs to get done by the draw dispose
}

/*
void initGuy(struct actor self) {
    self.pos.coords.x = 500;
    self.pos.coords.y = 500;
    self.drawRoutine = drawGuy;
    self.serviceRoutine = serviceGuy;

    // TODO: this wastes a lot of memory by loading separately for every instance of the same actor
    // assets should be loaded somewhere global with a register of who is using which sprites
    self.sprite = al_load_bitmap("assets/guy.png");\
    // sprite should also be a pointer to a location in a spritesheet to allow for animation and poses, gotta figure out how the ALLEGRO_BITMAP works to do that
    if (!self.sprite) {
        // TODO error
    }

}

void serviceGuy(struct actor self) {

}

void disposeGuy(struct actor self) {
    al_destroy_bitmap(self.sprite);
}
*/

void disposeActors(void) {
    // TODO free() some stuff
}
