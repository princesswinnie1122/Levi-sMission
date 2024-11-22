#ifndef FRAME_H
#define FRAME_H

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

enum class ItemType {
    BlackTea, Broom, BrokenGlass, StinkySocks, Obstacle, Character
};

struct Item {
    ALLEGRO_BITMAP* bitmap;
    float x;
    float y;
    ItemType type;
    float width;
    float height;
    bool collectible;
    bool touched;
};

struct ItemData {
    const char* filePath;
    float x;
    float y;
    ItemType type;
    float width;
    float height;
    bool collectible;
    bool touched;
};

class Frame {
public:
    Frame();
    void Init();
    void Update(Levi& levi);
    void Draw();
    void Destroy();
    void Ding(Levi& levi);
    void HandleCollision(Item& item, Levi& levi);
    void Stop(ALLEGRO_EVENT &event);
    void Shift();
    bool PreventUp() const;
    bool PreventDown() const;

    int getLife() const;
    int getAtk() const;


private:

    float x;
    float speed;
    int life, atk;

    bool isDying;
    float dyingDuration;
    float dyingTimeElapsed;
    ALLEGRO_TIMER*frame_timer;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;

    bool preventUp;
    bool preventDown;

    std::vector<Item> items; // Changed from 'obstacles' to 'items'
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

#endif // FRAME_H
