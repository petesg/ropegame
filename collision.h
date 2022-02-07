#ifndef COLLISION_H
#define COLLISION_H

#include <stdio.h>

#include "structs.h"
#include "errors.h"

extern Collider* colliders;
extern uint32_t numColliders;

void initCollision(void);
Collider* addCollider(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
uint16_t getNearbyColliders(uint16_t pos[2], uint8_t radius, Collider** dest);
Collider* moveActor(Actor* a);

#endif // COLLISION_H
