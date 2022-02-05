#include "draw.h"

ALLEGRO_FONT* smallFont;

struct LoadedBitmap { // dict of loaded bitmaps
    ALLEGRO_BITMAP* bitmap;
    const char* fname;
} *loadedBitmaps;

uint16_t numLoadedBitmaps;

void initDraw(void) {

    al_init_image_addon();
    
    smallFont = al_create_builtin_font();

}

uint8_t d = 0;
void draw(void) {

    al_clear_to_color(al_map_rgb(0, 0, 0));

    char str[32];
    snprintf(str, 32, "Hello World! (%d)", d++);
    al_draw_text(smallFont, al_map_rgb(255, 255, 255), 0, 0, 0, str);

    // draw actors
    for (uint16_t i = 0; i < numActors; i++) {
        Actor* drawdActor = &actors[i];
        //printf("numActors: %d, looking at actor: %d, actorx: %d\n", numActors, i, drawdActor->pos[0]);
        al_draw_bitmap(actors[i].sprite.sheet, actors[i].pos[0], actors[i].pos[1], 0);
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
