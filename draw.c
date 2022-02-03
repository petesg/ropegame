#include "draw.h"

ALLEGRO_FONT* smallFont;

void initDraw(void) {

    al_init_image_addon();

    smallFont = al_create_builtin_font();

}

void draw(void) {

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(smallFont, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
    al_flip_display();

}

void disposeDraw(void) {

    al_destroy_font(smallFont);

}
