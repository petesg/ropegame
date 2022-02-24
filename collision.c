#include "collision.h"

Collider* colliders;    // list of all colliders
uint32_t numColliders;
Collider* tempCollider;
Collider* nearby[256];

void initCollision(void) {
    numColliders = 0;
    addCollider(50, 150, 125, 150);
    //addCollider(125, 150, 200, 225);
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
    glm_vec2_sub(newCollider->p2, newCollider->p1, newCollider->vec);
    newCollider->len = glm_vec2_norm(newCollider->vec);
    //newCollider->len = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    // precalculate some geometry for collision math
    /*newCollider->line.cos = fabs(x2 - x1) / newCollider->len;
    newCollider->line.sin = fabs(y2 - y1) / newCollider->len;
    newCollider->line.a = (y2 - y1) / (x2 - x1);
    newCollider->line.b = -1;
    newCollider->line.c = y2 - (y2 - y1) / (x2 - x1);
    newCollider->line.slopeNorm = sqrt(pow(newCollider->line.a, 2) + pow(newCollider->line.b, 2));*/
    printf("initialized collider (len %f)\n", newCollider->len);
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

    // (all position vectors are moved into the collider's frame [origin at p1])
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

    vec2 Pa, Vf, P0C, temp;
    float r;

    // calculate [global] Pa (attetmpted new position = P0 + v)
    glm_vec2_add(a->pos, a->v, Pa);

    //drawVec(a->v, a->pos);

    //double vMag = sqrt(pow(a->v[0], 2) + pow(a->v[1], 2));  // magnitude of v
    //uint16_t numSteps = vMag / (2 * a->hitboxRad);          // number of preliminary steps to check 
    //double norm[] = {a->v[0] / vMag, a->v[1] / vMag};       // normalized vector along direction of v
    //uint32_t goodPos[] = {a->pos[0], a->pos[1]};            // furthest forward position along v known to be safe (updated as we go along)
    //printf("-\nmoving an actor\n");
    uint8_t numNearby = getNearbyColliders(a->pos, a->hitboxRad);
    printf("\nmoving %p with r=%d from (%f, %f) at v=[%f, %f]\n", a, a->hitboxRad, a->pos[0], a->pos[1], a->v[0], a->v[1]);
    //printf("filtered colliders into %p\n", &nearby);
    for (uint8_t i = 0; i < numNearby; ++i) {

        printf("checking collision with %p: (%f, %f) - (%f, %f) [%f, %f] \n", nearby[i], nearby[i]->p1[0], nearby[i]->p1[1], nearby[i]->p2[0], nearby[i]->p2[1], nearby[i]->vec[0], nearby[i]->vec[1]);

        // move Pa, P0 into collider frame
        glm_vec2_sub(Pa, nearby[i]->p1, Pa);
        glm_vec2_sub(a->pos, nearby[i]->p1, P0C);

        //drawVec(Pa, nearby[i]->p1);
        //drawVec(P0C, nearby[i]->p1);
        //drawVec(nearby[i]->vec, nearby[i]->p1);

        // check tip distance
        r = fabs(glm_vec2_cross(Pa, nearby[i]->vec)) / glm_vec2_norm(nearby[i]->vec);
        printf("distance is %f\n", r);

        if (r <= a->hitboxRad) {
            // v tip collision detected
            //glm_vec2_normalize_to(a->v, temp);
            // calculate Vf (fixed velocity)
            glm_vec2_scale_as(a->v, (r - a->hitboxRad) * glm_vec2_norm(Pa) * glm_vec2_norm(nearby[i]->vec) / glm_vec2_dot(Pa, nearby[i]->vec), Vf);
            // calculate d (local 1D coordinate of Pc' along collider)
            //glm_vec2_add(P0C, Vf, temp);
            glm_vec2_add(Pa, Vf, temp);
            drawVec(Pa, nearby[i]->p1);
            drawVec(temp, nearby[i]->p1);
            float d = glm_vec2_dot(temp, nearby[i]->vec) / glm_vec2_norm(P0C);
            printf("collision possible (d=%f), Vfixed=[%f, %f]\n", d, Vf[0], Vf[1]);
            // determine if collision is on flat
            if (d < 0) {
                if (-d > a->hitboxRad) {
                    // collision missed
                    continue;
                }
                else {
                    // collision at corner
                    // TODO calculate better fixed position
                    glm_vec2_add(a->v, Vf, a->v);
                }
            }
            else if (d > nearby[i]->len) {
                if (d > nearby[i]->len + a->hitboxRad) {
                    // collision missed
                    continue;
                }
                else {
                    // collision at corner
                    // TODO calculate better fixed position
                    glm_vec2_add(a->v, Vf, a->v);
                }
            }
            else {
                // collision is on flat
                    glm_vec2_add(a->v, Vf, a->v);
            }
            // TODO TEMP fix velocity (actually gotta make sure on flat first)
            //glm_vec2_copy(Vf, a->v);
            /*a->v[0] = 0;
            a->v[1] = 0;*/
            //return nearby[i];
            
        } // (r <= a->hitboxRad)
        
        // check distance from each endpoint point to v vector

        // check intersection of lines

        // move Pa back into global frame
        glm_vec2_add(Pa, nearby[i]->p1, Pa);
    }
    
    // move along fixed V
    glm_vec2_add(a->pos, a->v, a->pos); // TODO do we really want to do this here?

    return NULL;
}

bool testCollision(uint32_t* p1, uint32_t* p2, uint32_t* p3, uint16_t r) {
    return false;
}
