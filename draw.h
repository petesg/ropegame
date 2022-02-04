#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "errors.h"
#include "actors.h"

void initDraw(void);
void draw(void);
void disposeDraw(void);

//void drawGuy(struct actor self);

#endif // DRAW_H
