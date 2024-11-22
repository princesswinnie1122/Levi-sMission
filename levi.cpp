#include "levi.h"
#include "frame.h"
#include "GameWindow.h"
#include <cmath>

Levi::Levi(): stop(0), jump(true), gameEnd(false) {
}

void Levi::Init() {
    x = -800;
    y = 300;
    framecount = 0;

    width = 150;
    height = 125;

    levi_timer = al_create_timer(1.0 / 60.0);
    al_start_timer(levi_timer);

    char buffer[15];
    for (int i = 1; i <= 2; i++) {
        sprintf(buffer, "./images/run_%d.png", i);
        ALLEGRO_BITMAP* img = al_load_bitmap(buffer);

        imgData[LeviState::RUNNING].push_back(img);
    }

    die = al_load_bitmap("./images/dead.png");
    isDying = false;
    dyingDuration = 2.5;
    dyingTimeElapsed = 0.0;

    shimmeringDuration = 1.5;
    shimmeringTimeElapsed = 0.0;
}

float Levi::getX() const { return x; }
float Levi::getY() const { return y; }
int Levi::getWidth() const { return width; }
int Levi::getHeight() const { return height; }

void Levi::Die() {
    isDying = true;
    dyingTimeElapsed = 0.0;
    shimmeringTimeElapsed = 0.0;
}

int Levi::Stop() const {
    return stop;
}

bool Levi::Shimmering() const {
    return isShimmering;
}

bool Levi::Jump() const{
    return jump;
}

void Levi::Continue() {
    x += 0.5;
}

bool Levi::End() const{
    return gameEnd;
}

void Levi::resetEnd(){
    gameEnd = false;
}

void Levi::Update(double deltaTime) {
    if(x <= 200) x += 0.5;
    else if(x > 1800) gameEnd = true;
    else{
        jump = false;

        if (isDying) {
            stop = 1;
            dyingTimeElapsed += deltaTime * 1000;
            //printf("dying: %f\n", dyingTimeElapsed);
            if (dyingTimeElapsed >= dyingDuration) {
                isDying = false;
                isShimmering = true;
                dyingTimeElapsed = 0.0;
            }
        }

        if (isShimmering) {
            stop = 2;
            shimmeringTimeElapsed += deltaTime;
            //printf("shimmer: %f \n", shimmeringTimeElapsed);
            if (shimmeringTimeElapsed >= shimmeringDuration) {
                isShimmering = false;
                shimmeringTimeElapsed = 0.0;
                stop = 0;
            }
        }
    }

    if (!stop) {
        switchRate = 200;
        framecount++;
        if (framecount >= 2 * switchRate) {
            framecount = 0;
        }
    }
}

void Levi::moveUp() {
    if(y > 170 && x > 200) y -= 135;
}

void Levi::moveDown() {
    if(y < 830 && x > 200) y += 135;
}

void Levi::Draw() {
    int frameIndex = (framecount < switchRate) ? 0 : 1;
    ALLEGRO_BITMAP* current_frame = imgData[LeviState::RUNNING][frameIndex];

    if (isDying) {
    al_draw_bitmap(die, x, y, 0);
    } else if (isShimmering) {
        if (static_cast<int>(shimmeringTimeElapsed * 10) % 2 == 0) {
            al_draw_bitmap(current_frame, x, y, 0);
        }
    } else {
        al_draw_bitmap(current_frame, x, y, 0);
    }
}


Levi::~Levi() {
    al_destroy_timer(levi_timer);
    al_destroy_bitmap(die);

    for (auto& state : imgData) {
        for (auto& img : state.second) {
            if (img) {
                al_destroy_bitmap(img);
                img = nullptr;
            }
        }
    }
    imgData.clear();
}




