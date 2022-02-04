#include <stdio.h>
#include <stdbool.h>
#include <stdint-gcc.h>

#include <allegro5/allegro5.h>

#include "actors.h"
#include "draw.h"

bool bootup(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* frameTimer, ALLEGRO_DISPLAY* disp) {

    // allocates basic engine resources and registers necessary Allegro mechanics

    if(!al_init())
    {
        printf("couldn't initialize allegro\n");
        return 0;
    }
    if(!al_install_keyboard())
    {
        printf("couldn't initialize keyboard\n");
        return 0;
    }

    frameTimer = al_create_timer(1.0 / 30.0);
    if(!frameTimer)
    {
        printf("couldn't initialize timer\n");
        return 0;
    }
    queue = al_create_event_queue();
    if(!queue)
    {
        printf("couldn't initialize queue\n");
        return 0;
    }
    disp = al_create_display(1920, 1080); // TODO figure out fullscreen?
    if(!disp)
    {
        printf("couldn't initialize display\n");
        return 0;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(frameTimer));

    return 1;
}

int main()
{

    // allegro init

    printf("starting allegro NEW TEXT\n");

    al_init();
    al_install_keyboard();

    ALLEGRO_TIMER* frameTimer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    printf("booting up");

    bootup(queue, frameTimer, disp);
/*

    printf("some shit gone done fucky");

    // engine init

    //initActors();
    initDraw();

    // game loop

    printf("starting main loop");

    bool redraw = true;
    bool exit = false;
    ALLEGRO_EVENT event;
    al_start_timer(frameTimer);
    while(!exit)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit = true;
                break;
        }

        if(redraw && al_is_event_queue_empty(queue))
        {
            draw();
            redraw = false;
        }

    }

    // cleanup

    disposeDraw();
*/

    al_destroy_display(disp);
    al_destroy_timer(frameTimer);
    al_destroy_event_queue(queue);
    return 0;
}
