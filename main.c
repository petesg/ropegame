#include <stdio.h>
#include <stdbool.h>
#include <stdint-gcc.h>

#include <allegro5/allegro5.h>

#include "actors.h"
#include "draw.h"
#include "collision.h"

ALLEGRO_TIMER* frameTimer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* disp;

int bootupAllegro(void) {

    if(!al_init()) {
        printf("couldn't initialize allegro\n");
        return 0;
    }

    if(!al_install_keyboard()) {
        printf("couldn't initialize keyboard\n");
        return 0;
    }

    frameTimer = al_create_timer(1.0 / 30.0);
    if(!frameTimer) {
        printf("couldn't initialize timer\n");
        return 0;
    }

    queue = al_create_event_queue();
    if(!queue) {
        printf("couldn't initialize queue\n");
        return 0;
    }

    disp = al_create_display(480, 320); // TODO fullscreen?  calculate display size?  adjustable?
    if(!disp) {
        printf("couldn't initialize display\n");
        return 0;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(frameTimer));

    return 1;
}

void cleanupAllegro(void) {
    al_destroy_display(disp);
    al_destroy_timer(frameTimer);
    al_destroy_event_queue(queue);
}

int main()
{

    if (!bootupAllegro())
        return 1;
    initDraw();
    initActors();
    initCollision();

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(frameTimer);
    while(!done) {
        al_wait_for_event(queue, &event);

        // TODO this should be in a while(event queue is not empty) loop
        switch(event.type) {
            case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                serviceActors();
                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                /*serviceActors();
                redraw = true;*/
                actors[0].v[1] = -7;
                actors[0].pos[1] = 100;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(redraw && al_is_event_queue_empty(queue)) {
            /*al_clear_to_color(al_map_rgb(0, 0, 0));
            //al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello world!");
            al_flip_display();*/
            draw();
            redraw = false;
        }
    }

    disposeDraw();
    disposeActors();
    cleanupAllegro();

    return 0;

/*
    // allegro init

    printf("starting allegro\n");

    al_init();

    printf("HERE ONE/n");
    
    al_install_keyboard();

    ALLEGRO_TIMER* frameTimer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    printf("booting up");

    bootup(queue, frameTimer, disp);


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


    al_destroy_display(disp);
    al_destroy_timer(frameTimer);
    al_destroy_event_queue(queue);
    return 0;*/
}
