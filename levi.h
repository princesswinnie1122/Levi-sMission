#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <map>

#include "global.h"

enum class LeviState
{
    UP,
    DOWN,
    RUNNING
};

class Levi{

public:
    Levi();
    ~Levi();
    void Init();
    void Update(double deltaTime);
    void Draw();

    void moveUp();
    void moveDown();

    void stun();
    bool isStunned() const;

    float getX() const;
    float getY() const;
    int getWidth() const;
    int getHeight() const;

    void preventPassing();
    void resetRestriction();

    void Die();
    bool Dying() const;
    bool Shimmering() const;
    int Stop() const;

    bool Jump() const;
    void Continue();

    bool End() const;
    void resetEnd();

private:
    bool gameEnd;

    float x, y;
    int framecount;
    int switchRate;
    int width;
    int height;

    bool isDying;
    float dyingDuration;
    float dyingTimeElapsed;
    ALLEGRO_BITMAP* die;

    bool isShimmering;
    float shimmeringDuration;
    float shimmeringTimeElapsed ;

    int stop;
    bool jump;

    ALLEGRO_TIMER*levi_timer;
    LeviState state;
    std::map< LeviState, std::vector<ALLEGRO_BITMAP*> > imgData;
    std::map< LeviState, int> imgCount;

    bool verticalMove;
};

#endif
