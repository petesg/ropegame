#ifndef COLLISION_H
#define COLLISION_H

#include <stdio.h>
#include <math.h>

#include <cglm/cglm.h>

#include "structs.h"
#include "errors.h"

extern Collider* colliders;
extern uint32_t numColliders;

void initCollision(void);
Collider* addCollider(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
uint8_t getNearbyColliders(uint32_t pos[2], uint8_t radius);
Collider* moveActor(Actor* a);
bool testCollision(uint32_t* p1, uint32_t* p2, uint32_t* p3, uint16_t r);
double inline distToLine(uint32_t p[], Line* l);

#endif // COLLISION_H
