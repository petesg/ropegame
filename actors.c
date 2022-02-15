#include "actors.h"

Actor* actors;      // dynamic array of all actors in game
int numActors = 0;  // size of actors array
Actor* tempActor;   // dummy memory block for setting up new actors or defaulting to when out of memory

void initActors(void) {

    printf("actors init\n");

    // add special actors here
    addActor(initGuy);
    tempActor = addActor(initGuy);
    tempActor->pos[0] = 160;
    tempActor->pos[1] = 80;
    tempActor->sprite.tile = 44;
    tempActor->v[1] = -5;

    printf("added guy (%d, %d) - %p\n", actors[0].pos[0], actors[0].pos[1], &actors[0]);
    printf("second guy tile is %d\n", actors[1].sprite.tile);

}

Actor* addActor(void (*newInitRoutine)(Actor*)) {
    printf("adding actor to actors[%d]\n", numActors);
    Actor* tempPtr = realloc(actors, sizeof(Actor) * (numActors + 1));
    if (!tempPtr) {
        errorOutOfMemory();
        return tempActor; // TODO figure out how we really want to handle this
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

void serviceActors(void) {
    for (uint16_t i = 0; i < numActors; ++i) {
        actors[i].serviceRoutine(actors + i);
    }
}

void disposeActors(void) {
    // TODO free() some stuff
}


// 
// SPECIFIC ACTOR ROUTINES
//
////////////////////////////


void initGuy(Actor* self) {
    // start position
    self->pos[0] = 100;
    self->pos[1] = 100;
    self->v[0] = 0;
    self->v[1] = 0;
    
    // handling routines
    self->serviceRoutine = serviceGuy;
    self->disposeRoutine = disposeGuy;

    // hitbox
    self->hitboxRad = 11;
    
    // setup sprite
    self->sprite.sheet = getBitmap(ASSET_SH_GUY);
    if(!self->sprite.sheet) {
        // TODO complain
    }
    self->sprite.xOffset = 25;
    self->sprite.yOffset = 25;
    self->sprite.horTiles = 8;
    self->sprite.tileWidth = 50;
    self->sprite.tileHeight = 37;
    self->sprite.tile = 55;
    self->sprite.startTile = 55;
    self->sprite.animLen = 4;
    self->sprite.frameTimer = 8;
    self->sprite.frameDur = 3;

    printf("guy is initialized (%d, %d) - [%p]\n", self->pos[0], self->pos[1], self);
}

void serviceGuy(Actor* self) {
    // calculate v from physics
    //printf("servicing guy %p\n", self);
    double a[2] = {0, 0.5}; // base acceleration (gravity)
    // TODO calculate forces
    // ...
    self->v[0] += a[0];
    self->v[1] += a[1];

    // move by v
    //self->pos[0] += 1;
    Collider* hit = moveActor(self);
    //printf("moved guy\n");

    // TODO do I need to record forces from hit collider for next iteration?
    if (hit) {

    }
    //printf("servicing animation\n");
    serviceAnimation(&self->sprite);
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
