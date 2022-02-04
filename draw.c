#include "draw.h"

ALLEGRO_FONT* smallFont;

void initDraw(void) {

    al_init_image_addon();
    
    smallFont = al_create_builtin_font();

}

uint8_t d = 0;
void draw(void) {

    al_clear_to_color(al_map_rgb(0, 0, 0));

    char str[32];
    snprintf(str, 32, "Hello World! (%d)", d++);
    //al_draw_text(smallFont, al_map_rgb(255, 255, 255), 0, 0, 0, str);

    // draw actors
    /*for (uint16_t i = 0; i < numActors; i++) {
        actors[i].drawRoutine(actors[i]);
    }*/

    al_flip_display();

}

void disposeDraw(void) {

    al_destroy_font(smallFont);

}

/*void drawGuy(struct actor self) {
    al_draw_bitmap(self.sprite, self.pos.coords.x, self.pos.coords.y, 0);
}*/
