#include "draw.h"

ALLEGRO_FONT* smallFont;
bool showHitboxes = true;
vec2 vecs[256];
uint8_t numVecs;

struct LoadedBitmap { // dict of loaded bitmaps
    ALLEGRO_BITMAP* bitmap;
    const char* fname;
} *loadedBitmaps;

uint16_t numLoadedBitmaps;

void initDraw(void) {

    al_init_image_addon();
    al_init_primitives_addon();
    
    smallFont = al_create_builtin_font();

}

uint8_t d = 0;
void draw(void) {

    al_clear_to_color(al_map_rgb(0, 0, 0));

    char str[32];
    snprintf(str, 32, "Hello World! (%d)", d++);
    al_draw_text(smallFont, al_map_rgb(255, 255, 255), 0, 0, 0, str);

    // draw actors
    for (uint16_t i = 0; i < numActors; ++i) {
        //Actor* drawdActor = &actors[i];
        //printf("numActors: %d, looking at actor: %d, actorx: %d\n", numActors, i, drawdActor->pos[0]);
        Sprite* s = &actors[i].sprite;
        ALLEGRO_BITMAP* tile = al_create_sub_bitmap(s->sheet, s->tileWidth * (s->tile % s->horTiles), s->tileHeight * (s->tile / s->horTiles), s->tileWidth, s->tileHeight);
        // TODO measure if this is the fastest way to do this or should the sub bitmap only be calculated when frame changes?
        al_draw_bitmap(tile, actors[i].pos[0] - s->xOffset, actors[i].pos[1] - s->yOffset, 0);
        al_destroy_bitmap(tile);
        if (showHitboxes) {
            al_draw_circle(actors[i].pos[0], actors[i].pos[1], actors[i].hitboxRad, al_map_rgb(0, 180, 0), 1);
        }
    }

    // draw colliders
    if (showHitboxes) {
        for (uint32_t i = 0; i < numColliders; ++i) {
            Collider* c = &colliders[i];
            al_draw_line(c->p1[0], c->p1[1], c->p2[0], c->p2[1], al_map_rgb_f(1, 0, 0), 1);
        }
        for (uint8_t i = 0; i < numVecs; ++i) {
            al_draw_line(vecs[2*i][0], vecs[2*i][1], vecs[2*i+1][0], vecs[2*i+1][1], al_map_rgb_f(0, 0, 1), 1);
        }
        numVecs = 0;
    }

    al_flip_display();

}

void disposeDraw(void) {

    al_destroy_font(smallFont);

    // TODO destroy loadedBitmaps

}

// returns a bitmap of the requested file, file will be loaded from disk if it has not already been so
// this is not optimized for speed so try to call ahead of time
ALLEGRO_BITMAP* getBitmap(const char* fname) {
    // check if we've loaded the bitmap already
    for (uint16_t i = 0; i < numLoadedBitmaps; i++) {
        if (!strcmp(loadedBitmaps[i].fname, fname)) {
            printf("already loaded at [%d]\n", i);
            return loadedBitmaps[i].bitmap;
        }
    }

    // bitmap hasn't already been loaded, do it now
    printf("adding \"%s\" bitmap to loaded bitmaps[%d]\n", fname, numLoadedBitmaps);
    struct LoadedBitmap* tempPtr = realloc(loadedBitmaps, sizeof(struct LoadedBitmap) * (numLoadedBitmaps + 1));
    if (!tempPtr) {
        errorOutOfMemory();
        return tempPtr->bitmap; // TODO figure out how I really want to handle this
    }
    loadedBitmaps = tempPtr;
    struct LoadedBitmap* newLoad = loadedBitmaps + numLoadedBitmaps++; // pointer to newly added slot
    newLoad->bitmap = al_load_bitmap(fname);
    newLoad->fname = fname;
    printf("array resized (numLoadedBitmaps is now [%d])\n", numLoadedBitmaps);
    return newLoad->bitmap;
}

void serviceAnimation(Sprite* sprite) {
    if (sprite->frameTimer > 0 && !--(sprite->frameTimer)) {
        // advance frame and reset timer
        if (++(sprite->tile) > sprite->startTile + sprite->animLen)
            sprite->tile = sprite->startTile;
        sprite->frameTimer = sprite->frameDur;
    }
}

void drawVec(vec2 v, vec2 loc) {
    glm_vec2_copy(loc, vecs[2 * numVecs]);
    vec2 endPt;
    glm_vec2_add(loc, v, endPt);
    glm_vec2_copy(endPt, vecs[2 * numVecs++ + 1]);
}
