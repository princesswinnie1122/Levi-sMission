#include "GameWindow.h"
#include "global.h"
#include "story2.h"
#include <iostream>
#include <sstream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

Story2::Story2(): storyEnd(false) {
}

Story2::~Story2() {
}

void Story2::Init() {
    levi_bg = al_load_bitmap("./images/levi_2.png");
    erwin_bg = al_load_bitmap("./images/erwin_2.png");

    textIndex = 0;
    leviTurn = true; // Start with Levi
    lastCharTime = 0;
    font = al_load_ttf_font("./fonts/times.ttf", 36, 0);
    font_large = al_load_ttf_font("./fonts/times_bold.ttf", 42, 0);
    dialogueStage = 1;
    currentText = "Levi, this mission is to retrieve ten vials of spinal fluid that the Marleyan troops\ndropped outside the walls during the last battle.";

    al_reserve_samples(2);

    sample = al_load_sample("./audio/story_1.wav");
    story1 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(story1, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(story1, al_get_default_mixer());
    al_set_sample_instance_gain(story1, 1) ;
}

void MultilineText(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y, int flags, const std::string& text) {
    std::istringstream iss(text);
    std::string line;
    float lineHeight = al_get_font_line_height(font);

    while (std::getline(iss, line)) {
        al_draw_text(font, color, x, y, flags, line.c_str());
        y += lineHeight; // Move to the next line position
    }
}

bool Story2::End() const{
    return storyEnd;
}

void Story2::Update(ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_EVENT event;
    double currentTime = al_get_time();
    int story = 2;

    if(al_get_next_event(event_queue, &event)) {
        if ((event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_SPACE) ||
            event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            dialogueStage++;
            if (story == 2) {
                switch (dialogueStage) {
                    case 2: currentText = "Just retrieval, huh? Sounds straightforward enough."; break; //er
                    case 3: currentText = "It's a top-secret operation. I want you to go alone and avoid direct confrontation\nwith the Titans as much as possible."; break; //le
                    case 4: currentText = "It's crucial we get those vials back without alerting anyone to their significance."; break;
                    case 5: currentText = "A solo mission... It's risky, but stealth is my specialty. I'm ready to go."; break; //le
                    case 6:
                        storyEnd = true;
                        break;
                }
            }
            textIndex = 0; // Reset text index for new dialogue
            lastCharTime = currentTime;
        }
        if (currentTime - lastCharTime > 0.03 && textIndex < currentText.length()) {
            textIndex++;
            lastCharTime = currentTime;
        }
    }
}


void Story2::Draw(){
    al_play_sample_instance(story1);
    if(dialogueStage==4) al_draw_bitmap(erwin_bg, 0, 0, 0);
    else if(dialogueStage==5) al_draw_bitmap(levi_bg, 0, 0, 0);
    else if (dialogueStage%2==1) {
        al_draw_bitmap(erwin_bg, 0, 0, 0);
    } else {
        al_draw_bitmap(levi_bg, 0, 0, 0);
    }

    std::string textToShow = currentText.substr(0, textIndex);
    if (dialogueStage == 1 || dialogueStage == 3 || dialogueStage == 5){
        MultilineText(font, WHITE, 310, 865, ALLEGRO_ALIGN_LEFT, textToShow.c_str());
    } else {
        al_draw_text(font, WHITE, 310, 865, 0, textToShow.c_str());
    }

    if(dialogueStage == 6) al_stop_sample_instance(story1);
}

void Story2::Destroy(){
    al_destroy_bitmap(levi_bg);
    al_destroy_bitmap(erwin_bg);
    al_destroy_sample_instance(story1);
}

