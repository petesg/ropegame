#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint-gcc.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef struct ACTOR Actor;

typedef struct {
    ALLEGRO_BITMAP* sheet;
    uint16_t tileWidth;
    uint16_t tileHeight;
    uint8_t horTiles;
    uint16_t frameIndex;
} Sprite;

struct ACTOR {
    uint32_t pos[2];
    double v[2];
    //ALLEGRO_BITMAP* sprite; // TODO figure out how to store sprites
    Sprite sprite;
    uint8_t frameIndex;
    void (*initRoutine)(Actor*);
    void (*serviceRoutine)(Actor*);
    void (*disposeRoutine)(Actor*);
};

#endif // STRUCTS_H
