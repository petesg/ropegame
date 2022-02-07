#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <string.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "structs.h"
#include "errors.h"
#include "actors.h"
#include "assets.h"
#include "collision.h"

/*typedef struct {
    ALLEGRO_BITMAP* sheet;
    uint16_t tileWidth;
    uint16_t tileHeight;
    uint8_t horTiles;
    uint16_t frameIndex;
} Sprite;*/

void initDraw(void);
void draw(void);
void disposeDraw(void);
void serviceAnimation(Sprite* sprite);

extern ALLEGRO_DISPLAY* disp;

ALLEGRO_BITMAP* getBitmap(const char* fname);

#endif // DRAW_H
