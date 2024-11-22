#ifndef FRAME2_H
#define FRAME2_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "./algif5/src/algif.h"
#include <vector>
#include <functional>
#include "levi.h"
#include "frame.h"

enum class ItemType2 {
    Tube, Obstacle, Titan
};

struct Item2 {
    ALLEGRO_BITMAP* bitmap;
    float x;
    float y;
    ItemType2 type;
    float width;
    float height;
    bool collectible;
    bool touched;
};

struct ItemData2 {
    const char* filePath;
    float x;
    float y;
    ItemType2 type;
    float width;
    float height;
    bool collectible;
    bool touched;
};

class Frame2 {
public:
    Frame2();
    void Init(Frame& frame);
    void Update(Levi& levi);
    void Draw();
    void Destroy();
    void Ding(Levi& levi);
    void HandleCollision(Item2& item2, Levi& levi);
    void Stop(ALLEGRO_EVENT &event);
    void Shift();
    bool PreventUp() const;
    bool PreventDown() const;

    bool failGame() const;
    int Tube() const;

private:
    bool fail = false;

    float x;
    float speed;
    int life, atk;
    int tube;

    bool isDying;
    float dyingDuration;
    float dyingTimeElapsed;
    ALLEGRO_TIMER*frame_timer;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;

    bool preventUp;
    bool preventDown;

    std::vector<Item2> items; // Changed from 'obstacles' to 'items'
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_BITMAP *ding = NULL;
    ALLEGRO_BITMAP *key;
    ALLEGRO_BITMAP *gain;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *dingSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *oi = NULL;
    ALLEGRO_SAMPLE_INSTANCE *hit = NULL;

    bool showDing = false;
    float dingX, dingY;
    double dingStartTime;
    const double dingDuration = 0.3;

    float currentPauseTime;
    float pauseDuration;
    bool isPaused;

};

#endif // FRAME2_H
