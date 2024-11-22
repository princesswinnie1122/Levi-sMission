#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>

class Menu {
public:
    Menu();
    ~Menu();
    void Init();
    bool Update(ALLEGRO_EVENT_QUEUE* event_queue);
    void Draw();
    void Destroy();

private:
    ALLEGRO_BITMAP* frames[115];
    ALLEGRO_BITMAP* title = NULL;
    ALLEGRO_BITMAP* click = NULL;
    ALLEGRO_TIMER *timer = NULL;

    int currentFrame;
    int mouseX, mouseY;

    double lastFrameSwitchTime;
    float trans;
    bool transIncrease;

};

#endif // MENU_H
