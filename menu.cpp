#include "GameWindow.h"
#include "menu.h"

Menu::Menu() {
}

Menu::~Menu() {
}

void Menu::Init() {
    title = al_load_bitmap("./images/title.png");
    click = al_load_bitmap("./images/click.png");
    trans = 1.0;
    transIncrease = false;

    for (int i = 0; i < 115; ++i) {
        std::string filename = "./menu/" + std::to_string(i+1) + ".png";
        frames[i] = al_load_bitmap(filename.c_str());
    }
    currentFrame = 0;
    lastFrameSwitchTime = al_get_time();
}

bool Menu::Update(ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_EVENT event;

    while (al_get_next_event(event_queue, &event)) {
        static double lastAlphaUpdateTime = al_get_time();
        if (al_get_time() - lastAlphaUpdateTime >= 1.0) {
            transIncrease = !transIncrease;
            lastAlphaUpdateTime = al_get_time();
        }
        if (transIncrease) {
            trans += 0.02;
        } else {
            trans -= 0.02;
        }
        trans = std::max(0.2f, std::min(1.0f, trans));
        //printf("Transparency: %f\n", trans);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            if (al_get_time() - lastFrameSwitchTime >= 0.1) {
                currentFrame = (currentFrame + 1) % 115;
                lastFrameSwitchTime = al_get_time();
                //printf("Frame updated to: %d\n", currentFrame);
            }
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
            //printf("Mouse click at: (%d, %d)\n", mouseX, mouseY);
            if (mouseX > 681 && mouseX < 681 + 439 && mouseY > 786 && mouseY < 786 + 67){
                //printf("Exiting menu loop.\n");
                return true;
            }
        }
    }
    return false;
}


void Menu::Draw() {
    //printf("Drawing frame: %d\n", currentFrame);
    al_draw_bitmap(frames[currentFrame], 0, 0, 0);
    al_draw_bitmap(title, 522, 280, 0);

    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
    ALLEGRO_COLOR tint = al_map_rgba_f(1.0, 1.0, 1.0, trans);
    al_draw_tinted_bitmap(click, tint, 681, 786, 0);
}

void Menu::Destroy(){
    for(int i=0; i<115; i++)
        al_destroy_bitmap(frames[i]);

    al_destroy_bitmap(title);
    al_destroy_bitmap(click);
}

