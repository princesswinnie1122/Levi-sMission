#ifndef STORY2_H
#define STORY2_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <functional>

class Story2 {
public:
    Story2();
    ~Story2();
    void Init();
    void Update(ALLEGRO_EVENT_QUEUE* event_queue);
    void Draw();
    void Destroy();
    void SetEndCallback(std::function<void()> callback);

    bool End() const;

private:
    ALLEGRO_BITMAP *levi_bg = NULL;
    ALLEGRO_BITMAP *erwin_bg = NULL;
    ALLEGRO_BITMAP *home_bg = NULL;
    ALLEGRO_BITMAP *trans_1 = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *story1 = NULL;

    ALLEGRO_FONT *font;
    ALLEGRO_FONT *font_large;
    std::string currentText;
    size_t textIndex;
    bool leviTurn;
    double lastCharTime;
    int dialogueStage;

    bool storyEnd;
};

#endif // STORY2_H
