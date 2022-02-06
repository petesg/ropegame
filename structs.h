#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint-gcc.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef struct ACTOR Actor;

typedef struct {
    ALLEGRO_BITMAP* sheet;
    uint16_t tileWidth; // TODO add an offset?
    uint16_t tileHeight;
    uint8_t horTiles;
    uint16_t tile;
} Sprite;

struct ACTOR {
    uint32_t pos[2];
    double v[2];
    Sprite sprite;
    void (*initRoutine)(Actor*);
    void (*serviceRoutine)(Actor*);
    void (*disposeRoutine)(Actor*);
};

#endif // STRUCTS_H
