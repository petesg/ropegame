#include "collision.h"

Collider* colliders;    // list of all colliders
uint32_t numColliders;
Collider* tempCollider;
Collider* nearby[256];

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
    // initialize new collider
    newCollider->p1[0] = x1;
    newCollider->p1[1] = y1;
    newCollider->p2[0] = x2;
    newCollider->p2[1] = y2;
    glm_vec2_sub(newCollider->p1, newCollider->p2, newCollider->vec);
    newCollider->len = glm_vec2_norm(newCollider->vec);
    //newCollider->len = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    // precalculate some geometry for collision math
    /*newCollider->line.cos = fabs(x2 - x1) / newCollider->len;
    newCollider->line.sin = fabs(y2 - y1) / newCollider->len;
    newCollider->line.a = (y2 - y1) / (x2 - x1);
    newCollider->line.b = -1;
    newCollider->line.c = y2 - (y2 - y1) / (x2 - x1);
    newCollider->line.slopeNorm = sqrt(pow(newCollider->line.a, 2) + pow(newCollider->line.b, 2));*/
    printf("initialized collider\n");
    return newCollider;
}

uint8_t getNearbyColliders(float pos[2], uint8_t radius) {
    //  TODO actually do some filtering
    //printf("starting filter on %d colliders\n", numColliders);
    //*dest = malloc(sizeof(Collider*) * numColliders);
    uint8_t numFound = 0;
    //printf("allocated %d bytes at %p", sizeof(Collider*) * numColliders, dest);
    for (uint16_t i = 0; i < numColliders; ++i) {
        //printf(" c[%d]=%p:", i, &colliders[i]);
        nearby[numFound++] = &colliders[i]; // TODO this line is somehow causing a stack smashing detection upon exiting the calling moveActor, absolutley no clue why
        //printf("filled %p with %p -", &nearby[i], nearby[i]);
        if (!numFound) {
            // TODO handle overflow
        }
    }
    //printf("done\n");
    return numFound;
}

// moves the actor along its velocity vector
// if a collision is detected, pointer to interfering collider will be returned TODO: probably should return some form of resulting force/impulse/velocity?
Collider* moveActor(Actor* a) {

    // TODO change this whole method.
    // new method:
    // First, for both ends of collider in question along with the endpoint of the located v vector,
    // project that point onto the other line, if <R then collision is detected.  If that test passes
    // with no collision, check for intersection of two line segments.

    // 1. calculate r = |Pa x C|/|C|
    //  - if r > R : DONE (no collision)
    //  - else : continue...
    // 2. calculate Pf  = Pa - Va * (R - r) / Cos(theta)
    //              Pc' = Pf * C / (C * C) * C
    //              d   = Pc' * C
    //  - if (d > 0 && d < |C|) : DONE (collision on flat)
    //  - else continue...
    // 3. solve intersection about corner
    //  - ...
    //
    // (* = dot product)

    vec2 Pa, temp;
    glm_vec2_add(a->pos, a->v, Pa);

    //double vMag = sqrt(pow(a->v[0], 2) + pow(a->v[1], 2));  // magnitude of v
    //uint16_t numSteps = vMag / (2 * a->hitboxRad);          // number of preliminary steps to check 
    //double norm[] = {a->v[0] / vMag, a->v[1] / vMag};       // normalized vector along direction of v
    //uint32_t goodPos[] = {a->pos[0], a->pos[1]};            // furthest forward position along v known to be safe (updated as we go along)
    //printf("-\nmoving an actor\n");
    uint8_t numNearby = getNearbyColliders(a->pos, a->hitboxRad);
    //printf("filtered colliders into %p\n", &nearby);
    for (uint8_t i = 0; i < numNearby; ++i) {
        fabs(glm_vec2_cross(Pa, nearby[i]->vec)) / glm_vec2_norm(nearby[i]->vec);
        //printf("-found nearby: %p\n", nearby[i]);
        // check distance from each endpoint point to v vector

        // check distance from endpoint of v vector to collider line
        // check intersection of lines
    }
    
    /*
    a->pos[0] += a->v[0];
    a->pos[1] += a->v[1];
    */
    glm_vec2_add(a->pos, a->v, a->pos);


    //printf("moved an actor\n");

    return NULL;
}

bool testCollision(uint32_t* p1, uint32_t* p2, uint32_t* p3, uint16_t r) {
    return false;
}
