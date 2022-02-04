#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <string.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "errors.h"
#include "actors.h"
#include "assets.h"

typedef struct {
    ALLEGRO_BITMAP* spriteSheet;
    uint16_t tileWidth;
    uint16_t tileHeight;
    uint8_t horTiles;
    uint16_t frameIndex;
} Sprite;

void initDraw(void);
void draw(void);
void disposeDraw(void);

ALLEGRO_BITMAP* getBitmap(const char* fname);

#endif // DRAW_H
