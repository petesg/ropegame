#include <stdio.h>
#include <stdbool.h>
#include <stdint-gcc.h>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include "actors.h"
#include "draw.h"

int main()
{

    // allegro init

    printf("Hello World!\n");

    al_init();
    al_install_keyboard();

    ALLEGRO_TIMER* frameTimer;// = al_create_timer(1.0 / 30.0); // eventually unlock the fps
    ALLEGRO_EVENT_QUEUE* queue;// = al_create_event_queue();
    ALLEGRO_DISPLAY* disp;// = al_create_display(1920, 1080);

    bootup(queue, frameTimer, disp);

    /*al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(renameTimer));*/

    // other init

    initActors();

    // game loop

    bool redraw = true;
    ALLEGRO_EVENT event;
    al_start_timer(frameTimer);
    bool exit = false;
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

        /*al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;
        else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
            exit = true;

        if(redraw && al_is_event_queue_empty(queue))
        {
            draw();
            redraw = false;
        }*/

        // process input

        // update logic

        // draw

    }

    // cleanup

    disposeDraw();

    al_destroy_display(disp);
    al_destroy_timer(frameTimer);
    al_destroy_event_queue(queue);

    return 0;
}

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
