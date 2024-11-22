#include "GameWindow.h"
#include "global.h"
#include "story.h"
#include <iostream>
#include <sstream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

Story::Story() {
}

Story::~Story() {
}

void Story::Init() {
    levi_bg = al_load_bitmap("./images/levi.png");
    erwin_bg = al_load_bitmap("./images/erwin.png");
    home_bg = al_load_bitmap("./images/home.png");
    trans_1 = al_load_bitmap("./images/trans_1.png");

    textIndex = 0;
    leviTurn = true; // Start with Levi
    lastCharTime = 0;
    font = al_load_ttf_font("./fonts/times.ttf", 36, 0);
    font_large = al_load_ttf_font("./fonts/times_bold.ttf", 42, 0);
    dialogueStage = 1;
    currentText = "Erwin, you wanted to see me?";

    al_reserve_samples(2);

    sample = al_load_sample("./audio/story_1.wav");
    story1 = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(story1, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(story1, al_get_default_mixer());
    al_set_sample_instance_gain(story1, 1) ;
}

void drawMultilineText(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y, int flags, const std::string& text) {
    std::istringstream iss(text);
    std::string line;
    float lineHeight = al_get_font_line_height(font);

    while (std::getline(iss, line)) {
        al_draw_text(font, color, x, y, flags, line.c_str());
        y += lineHeight*1.5; // Move to the next line position
    }
}

void Story::SetEndCallback(std::function<void()> callback) {
    endCallback = callback;
}

void Story::Update(ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_EVENT event;
    double currentTime = al_get_time();
    int story = 1;

    if(al_get_next_event(event_queue, &event)) {
        if ((event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_SPACE) ||
            event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            dialogueStage++;
            if (story == 1) {
                switch (dialogueStage) {
                    case 2: currentText = "Yes Levi, we have an urgent mission outside the walls tomorrow."; break; //er
                    case 3: currentText = "An urgent mission? What are the details?"; break; //le
                    case 4: currentText = "I can't disclose much right now. But I need you to be prepared. It could get rough."; break; //er
                    case 5: currentText = "Understood. I'll be ready."; break; //le
                    case 6: currentText = "Levi leaves Erwin's office with his usual stoic expression, \nbut inside, he's contemplating deeply."; break; //trans
                    case 7: currentText = "If we're heading out tomorrow, I should clean up my room today."; break; //le
                    case 8: currentText = "Who knows if we'll even be able to return this time..."; break; //le
                    case 9:
                        story = 2;
                        if (endCallback) endCallback();
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


void Story::Draw(){
    al_play_sample_instance(story1);

    if (dialogueStage>6){
        al_draw_bitmap(home_bg, 0, 0, 0);
    } else if (dialogueStage == 6){
        al_draw_bitmap(trans_1, 0, 0, 0);
    } else if (dialogueStage%2==1) {
        al_draw_bitmap(levi_bg, 0, 0, 0);
    } else {
        al_draw_bitmap(erwin_bg, 0, 0, 0);
    }

    std::string textToShow = currentText.substr(0, textIndex);
    if (dialogueStage == 6){
        drawMultilineText(font_large, WHITE, 420, 452, ALLEGRO_ALIGN_LEFT, textToShow.c_str());
    } else {
        al_draw_text(font, WHITE, 310, 865, 0, textToShow.c_str());
    }

    if(dialogueStage == 9) al_stop_sample_instance(story1);
}

void Story::Destroy(){
    al_destroy_bitmap(levi_bg);
    al_destroy_bitmap(erwin_bg);
    al_destroy_sample_instance(story1);
}
