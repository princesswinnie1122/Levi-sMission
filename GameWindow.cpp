#include "GameWindow.h"
#include "global.h"
#include "story.h"
#include "story2.h"
#include "menu.h"
#include "levi.h"
#include "frame.h"
#include "frame2.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define max(a, b) ((a) > (b)? (a) : (b))

GameWindow::GameWindow() {
    if (!al_init()) show_err_msg(-1);
    printf("Game Initializing...\n");
    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    al_start_timer(timer);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("./fonts/Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("./fonts/Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("./fonts/Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
}

void
GameWindow::game_init()
{
    game1 = al_load_bitmap("./images/game_1.png");
    game2 = al_load_bitmap("./images/game_2.png");
    tutorial_1 = al_load_bitmap("./images/tutorial_1.png");
    fail = al_load_bitmap("./images/fail.png");

    win = al_load_bitmap("./images/win.png");
    lose = al_load_bitmap("./images/lose.png");

    al_reserve_samples(20);

    sample = al_load_sample("./audio/start.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());
    al_set_sample_instance_gain(startSound, 0.6) ;

    sample = al_load_sample("./audio/game1.wav");
    bgm1 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(bgm1, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgm1, al_get_default_mixer());
    al_set_sample_instance_gain(bgm1, 1) ;

    sample = al_load_sample("./audio/game2.wav");
    bgm2 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(bgm2, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(bgm2, al_get_default_mixer());
    al_set_sample_instance_gain(bgm2, 0.8) ;
}

void GameWindow::game1_draw() {
    al_draw_bitmap(game1, 0, 0, 0);
}

void GameWindow::game2_draw() {
    al_draw_bitmap(game2, 0, 0, 0);
}


void GameWindow::game_play() {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    double lastTime = al_get_time();

    srand(time(NULL));

    game_reset();
    game_begin();

    while (msg == 2) { // Story starts
        al_clear_to_color(WHITE);
        story.Update(event_queue);
        story.Draw();
        al_flip_display();
    }

    al_play_sample_instance(bgm1);
    al_clear_to_color(WHITE);

    while(showTutorial){
        al_wait_for_event(event_queue, &event);
         al_draw_bitmap(tutorial_1, 0, 0, 0);
         al_flip_display();
        if (event.type == ALLEGRO_EVENT_KEY_UP) {
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                break;
            }
        }
    }

    al_clear_to_color(WHITE);
    while (msg == 3) {
        double currentTime = al_get_time();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        game1_draw();
        frame.Update(levi);
        frame.Draw();
        levi.Update(deltaTime);
        levi.Draw();

        al_flip_display();
        process_event();

        if(levi.End()){
            msg=4;
            break;
        }
    }

    al_stop_sample_instance(bgm1);

    /*
    while(frame2.failGame()){
        al_clear_to_color(WHITE);
        al_draw_bitmap(fail, 0, 0, 0);
        al_flip_display();
    }
    */

    story2.Init();
    al_clear_to_color(WHITE);
    while (msg == 4) { // Story 2 starts
        story2.Update(event_queue);
        story2.Draw();
        al_flip_display();

        if(story2.End()){
            printf("msg = 5");
            msg = 5;
            break;
        }
    }

    al_play_sample_instance(bgm2);
    frame2.Init(frame);
    levi.Init();
    al_clear_to_color(WHITE);

    while (msg == 5){
        double currentTime = al_get_time();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        game2_draw();
        frame2.Update(levi);
        frame2.Draw();
        levi.Update(deltaTime);
        levi.Draw();

        al_flip_display();
        process_event();

        if(levi.getX() > 2000){
            msg = 6;
            break;
        }


    }

    al_stop_sample_instance(bgm2);

    al_clear_to_color(WHITE);
    while(msg == 6){
        if(frame2.Tube() >= 10){
            al_draw_bitmap(win, 0, 0, 0);
            al_flip_display();
        }

        else{
            al_draw_bitmap(lose, 0, 0, 0);
            al_flip_display();
        }
    }

    msg = game_run();
    show_err_msg(msg);
}


void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

void GameWindow::process_event() {
    ALLEGRO_EVENT ev;
    while (al_get_next_event(event_queue, &ev)) { // Use non-blocking call
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    levi.moveUp();
                    break;
                case ALLEGRO_KEY_DOWN:
                    levi.moveDown();
                    break;
            }
        }
    }
}

int GameWindow::game_update(){
}

int GameWindow::game_run(){

}

void GameWindow::game_begin() {
    story.SetEndCallback([this]() {
        this->msg = 3;
        printf("Story ended, setting msg to 3\n");
    });

    game_init();
    menu.Init();
    story.Init();
    frame.Init();
    levi.Init();

    al_clear_to_color(al_map_rgb(0, 0, 0));

    while (!(menu.Update(event_queue))) {
        al_play_sample_instance(startSound);
        menu.Draw();
        al_flip_display();
    }

    al_stop_sample_instance(startSound);
    menu.Destroy();

    msg = 2;
}


void GameWindow::game_reset(){

}

void GameWindow::game_destroy(){
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_bitmap(game1);
    al_destroy_bitmap(game2);
    al_destroy_bitmap(tutorial_1);

    al_destroy_sample(sample);
    al_destroy_sample_instance(bgm1);
    al_destroy_sample_instance(bgm2);
    al_destroy_sample_instance(startSound);
}
