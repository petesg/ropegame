#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint-gcc.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

typedef struct ACTOR Actor;

typedef struct {
    ALLEGRO_BITMAP* sheet;  // bitmap of spritesheet
    uint16_t tileWidth;     // pixel width of tiles in spritesheet
    uint16_t tileHeight;    // pixel height of tiles in spritesheet
    uint8_t horTiles;       // number of tiles horizontally in spritesheet
    uint16_t tile;          // currently displayed tile (top-left is 0)
    uint16_t startTile;     // index of first tile of current animation
    uint16_t animLen;       // number of frames in current animation
    int8_t frameDur;        // duration of each frame in current animation
    int8_t frameTimer;      // countdown timer to advance current frame of animation (-1 for no animation)
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
