#include "actors.h"

/*
struct actor* actors;      // dynamic array of all actors in game
uint16_t numActors; // size of actors array
struct actor* tempActor;    // dummy memory block for setting up new actors or defaulting to when out of memory

void bsfunc(bullshit bs) {
    return;
}

void initActors(void) {

    bullshit stupidbsvar;
    stupidbsvar.func = bsfunc;
    stupidbsvar.func(stupidbsvar);

    printf("actors init\n");
    tempActor = addActor();
    tempActor->pos.coords.x = 500;
    tempActor->pos.coords.y = 500;
    tempActor->initRoutine = initGuy;

    for (uint16_t i = 0; i < numActors; i++) {
        actors[i].initRoutine(actors[i]);
    }
}

struct actor* addActor(void) {
    struct actor *tempPtr = realloc(actors, sizeof(struct actor) * (numActors + 1));
    if (tempPtr == NULL) {
        errorOutOfMemory();
        return tempActor; // TODO figure out how I really want to handle this
    }
    return actors + numActors++; // doing it this way so there's no need to memcpy from a temp outside of addActor()
                                 // is that really necessary?  it's not like we're adding lots of actors on the fly
}

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
