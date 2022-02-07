#ifndef COLLISION_H
#define COLLISION_H

#include <stdio.h>
#include <math.h>

#include "structs.h"
#include "errors.h"

extern Collider* colliders;
extern uint32_t numColliders;

void initCollision(void);
Collider* addCollider(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
uint16_t getNearbyColliders(uint16_t pos[2], uint8_t radius, Collider** dest);
Collider* moveActor(Actor* a);
bool testCollision(uint32_t* p1, uint32_t* p2, uint32_t* p3, uint16_t r);

#endif // COLLISION_H
