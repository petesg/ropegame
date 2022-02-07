#include "collision.h"

Collider* colliders;    // list of all colliders
uint32_t numColliders;
Collider* tempCollider;

void initCollision(void) {
    numColliders = 0;
    addCollider(50, 150, 125, 150);
    addCollider(125, 150, 200, 225);
}

Collider* addCollider(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
    printf("adding collider to colliders[%d]\n", numColliders);
    Collider* tempPtr = realloc(colliders, sizeof(Collider) * (numColliders + 1));
    if (!tempPtr) {
        errorOutOfMemory();
        return tempCollider; // TODO figure out how we really want to handle this
    }
    colliders = tempPtr;
    printf("array resized (numColliders is still [%d])\n", numColliders);
    Collider* newCollider = colliders + numColliders++;
    // initialize new actor
    newCollider->p1[0] = x1;
    newCollider->p1[1] = y1;
    newCollider->p2[0] = x2;
    newCollider->p2[1] = y2;
    printf("initialized collider\n");
    return newCollider;
}

uint16_t getNearbyColliders(uint16_t pos[2], uint8_t radius, Collider** dest) {
    //  TODO actually do some filtering
    *dest = colliders;
    return numColliders;
}

// moves the actor along its velocity vector
// if a collision is detected, pointer to interfering collider will be returned
Collider* moveActor(Actor* a) {

    double vMag = sqrt(pow(a->v[0], 2) + pow(a->v[1], 2));  // magnitude of v
    uint16_t numSteps = vMag / (2 * a->hitboxRad);          // number of preliminary steps to check 
    double norm[] = {a->v[0] / vMag, a->v[1] / vMag};       // normalized vector along direction of v
    uint32_t goodPos[] = {a->pos[0], a->pos[1]};              // furthest forward position along v known to be safe (updated as we go along)

    for (uint16_t i = 0; i < numSteps; ++i) {

    }
    
    a->pos[0] += a->v[0];
    a->pos[1] += a->v[1];

    return NULL;
}

bool testCollision(uint32_t* p1, uint32_t* p2, uint32_t* p3, uint16_t r) {
    
}
