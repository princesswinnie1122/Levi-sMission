#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include "./algif5/src/algif.h"

#include <vector>
#include <list>
#include "levi.h"
#include "menu.h"
#include "story.h"
#include "story2.h"
#include "global.h"
#include "frame.h"
#include "frame2.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7
#define STORY_START 8
// clock rate
const float FPS = 60;

class GameWindow
{
public:
    // constructor
    GameWindow();

    // each process of scene
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();
    void game1_draw();
    void game2_draw();
    void process_event();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

public:
    bool done = false;
    int msg;

private:
    Levi levi;
    Menu menu;
    Story story;
    Story2 story2;
    Frame frame;
    Frame2 frame2;

    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *game1;
    ALLEGRO_BITMAP *game2;
    ALLEGRO_BITMAP *run_1;
    ALLEGRO_BITMAP *run_2;
    ALLEGRO_BITMAP *tutorial_1;
    ALLEGRO_BITMAP *fail;
    ALLEGRO_BITMAP *win;
    ALLEGRO_BITMAP *lose;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *bgm1 = NULL;
    ALLEGRO_SAMPLE_INSTANCE *bgm2 = NULL;

    float transitionAlpha;
    bool inTransition;
    double transitionStartTime;

    bool redraw = false;
    bool mute = false;
    bool showTutorial = true;

};


#endif // MAINWINDOW_H_INCLUDED

