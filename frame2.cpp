#include "frame2.h"
#include "frame.h"
#include "Levi.h"
#include "GameWindow.h"
#include <iostream>
#include <sstream>

#define DARK al_map_rgb(61, 59, 82)
using namespace std;

Frame2::Frame2() : x(0), speed(0.8), isPaused(false), pauseDuration(0), currentPauseTime(0), preventUp(false), preventDown(false) {
}

void Frame2::Init(Frame& frame) {
    life = frame.getLife();
    atk = frame.getAtk();

    if(life <= 0) fail = true;

    frame_timer = al_create_timer(1.0 / 60.0);
    al_start_timer(frame_timer);

    font = al_load_ttf_font("./fonts/PixelCombat.ttf",48,0);

    const ItemData2 itemData2[] = {
        //bonus
        {"./images/tube.png", 3335, 836, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 5090, 832, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 7790, 832, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 7933, 167, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 1462+8000, 576, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 2850+8000, 854, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 3510+8000, 165, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 5392+8000, 596, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 7833+8000, 440, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 1462+8000, 576, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 834+16000, 437, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 2594+16000, 439, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 2644+16000, 439, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 3792+16000, 576, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 5266+16000, 313, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 6980+16000, 170, ItemType2::Tube, 70, 145, true, false},
        {"./images/tube.png", 7150+16000, 703, ItemType2::Tube, 70, 145, true, false},

        //~8000
        {"./images/hole.png", 1901, 348, ItemType2::Obstacle, 282, 70, false, false},
        {"./images/rock.png", 2382, 627, ItemType2::Obstacle, 370, 70, false, false},
        {"./images/bush.png", 2852, 856, ItemType2::Obstacle, 325, 130, false, false},
        {"./images/house1.png", 3054, 94, ItemType2::Obstacle, 560, 300, false, false},
        {"./images/tree2.png", 4065, 400, ItemType2::Obstacle, 640, 300, false, false},
        {"./images/root.png", 5056, 145, ItemType2::Obstacle, 310, 100, false, false},
        {"./images/mushroom.png", 5282, 487, ItemType2::Obstacle, 164, 180, false, false},
        {"./images/titan.png", 5837, 597, ItemType2::Obstacle, 295, 400, false, false},
        {"./images/house2.png", 6114, 371, ItemType2::Obstacle, 844, 300, false, false},
        {"./images/fence.png", 7070, 758, ItemType2::Obstacle, 610, 200, false, false},
        {"./images/trunk.png", 7374, 228, ItemType2::Obstacle, 353, 170, false, false},

        //~16000
        {"./images/pond.png", 350+8000, 229, ItemType2::Obstacle, 656, 560, false, false},
        {"./images/boat.png", 1040+8000, 336, ItemType2::Obstacle, 307, 210, false, false},
        {"./images/tree2.png", 1790+8000, 350, ItemType2::Obstacle, 640, 650, false, false},
        {"./images/hole.png", 3042+8000, 870, ItemType2::Obstacle, 282, 93, false, false},
        {"./images/rock.png", 3140+8000, 350, ItemType2::Obstacle, 370, 210, false, false},
        {"./images/mud.png", 3718+8000, 167, ItemType2::Obstacle, 340, 125, false, false},
        {"./images/tree3.png", 4223+8000, 500, ItemType2::Obstacle, 396, 500, false, false},
        {"./images/bush.png", 4644+8000, 837, ItemType2::Obstacle, 327, 100, false, false},
        {"./images/horse.png", 5040+8000, 343, ItemType2::Obstacle, 267, 200, false, false},
        {"./images/shit.png", 5744+8000, 420, ItemType2::Obstacle, 123, 140, false, false},
        {"./images/castle.png", 5980+8000, 106, ItemType2::Obstacle, 918, 720, false, false},
        {"./images/stop.png", 7459+8000, 395, ItemType2::Obstacle, 219, 605, false, false},

        //~24000
        {"./images/rock.png", 436+16000, 744, ItemType2::Obstacle, 370, 210, false, false},
        {"./images/rock2.png", 1620+16000, 120, ItemType2::Obstacle, 324, 316, false, false},
        {"./images/root2.png", 1900+16000, 470, ItemType2::Obstacle, 390, 240, false, false},
        {"./images/mount1.png", 2820+16000, 395, ItemType2::Obstacle, 722, 592, false, false},
        {"./images/mount2.png", 4246+16000, 88, ItemType2::Obstacle, 780, 575, false, false},
        {"./images/castle2.png", 5528+16000, 500, ItemType2::Obstacle, 464, 453, false, false},
        {"./images/rock3.png", 6398+16000, 206, ItemType2::Obstacle, 418, 203, false, false},
        {"./images/house3.png", 7382+16000, 388, ItemType2::Obstacle, 518, 606, false, false},

        {"./images/titan_1.png", 355+16000, 298, ItemType2::Titan, 100, 250, false, false},
        {"./images/titan_1.png", 1188+16000, 440, ItemType2::Titan, 100, 250, false, false},
        {"./images/titan_1.png", 2533+16000, 560, ItemType2::Titan, 100, 250, false, false},
        {"./images/titan_1.png", 3595+16000, 174, ItemType2::Titan, 100, 250, false, false},
        {"./images/titan_1.png", 5100+16000, 560, ItemType2::Titan, 100, 250, false, false},
        {"./images/titan_1.png", 6790+16000, 580, ItemType2::Titan, 100, 250, false, false},
    };

    for (const auto& data : itemData2) {
        ALLEGRO_BITMAP* bitmap = al_load_bitmap(data.filePath);
        if (bitmap != nullptr) {
            Item2 item2 = {bitmap, data.x, data.y, data.type, data.width, data.height, data.collectible};
            items.push_back(item2);
        } else {
            printf("Failed to load item: %s\n", data.filePath);
        }
    }

    al_reserve_samples(10);

    ding = al_load_bitmap("./images/ding.png");
    key = al_load_bitmap("./images/key.png");
    gain = al_load_bitmap("./images/gain.png");

    sample = al_load_sample("./audio/ding.wav");
    dingSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(dingSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(dingSound, al_get_default_mixer());
    al_set_sample_instance_gain(dingSound, 1.5) ;

    sample = al_load_sample("./audio/oi.wav");
    oi = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(oi, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(oi, al_get_default_mixer());
    al_set_sample_instance_gain(oi, 0.9) ;

    sample = al_load_sample("./audio/hit_2.wav");
    hit = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hit, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(hit, al_get_default_mixer());
    al_set_sample_instance_gain(hit, 0.6) ;
}

bool Frame2::failGame() const{
    return fail;
}

int Frame2::Tube() const{
    return tube;
}


void Frame2::Update(Levi& levi) {

    if (levi.Stop()==0 && x >= -24000+1800 && !levi.Jump()){
        x -= speed;
    }

    if(x <= -24000+1800) levi.Continue();

    //if(!levi.Jump() && x > -1600) al_draw_bitmap(key, 150, 500, 0);

    auto it = items.begin();
    while (it != items.end()) {
        float itemX = x + it->x;
        float itemY = it->y;
        float itemWidth = it->width;
        float itemHeight = it->height;

        if (levi.getX() + levi.getWidth() < itemX + itemWidth && levi.getX() + levi.getWidth() > itemX &&
            levi.getY() + levi.getHeight() + 135 > itemY){
            preventDown = true;
        }

        if (levi.getX() + levi.getWidth() < itemX + itemWidth && levi.getX() + levi.getWidth() > itemX &&
            levi.getY() - 135 < itemY + itemHeight){
            preventUp = true;
        }

        if(levi.getX() + levi.getWidth() > itemX + 15 && levi.getX() + levi.getWidth() < itemX+itemWidth &&
           levi.getY() < itemY + itemHeight && levi.getY() + levi.getHeight() > itemY + 50){
            HandleCollision(*it, levi);
            if (it->collectible) {
                it = items.erase(it);
                if(it->type == ItemType2::Tube)
                    Ding(levi);
            } else {
                ++it;
            }
        }else {
            ++it;
        }
        //if (prevent) levi.preventPassing();
        //else levi.resetRestriction();
    }


}

bool Frame2::PreventUp() const{
    return preventUp;
}

bool Frame2::PreventDown() const{
    return preventDown;
}

void Frame2::HandleCollision(Item2& item2, Levi& levi) {
    switch (item2.type) {
        case ItemType2::Tube:
            tube++;
            break;
        case ItemType2::Obstacle:
            levi.Die();
            al_play_sample_instance(hit);
            if (!item2.touched && levi.Stop()==2) {
                printf("touched");
                life--;
                x += 350;
                item2.touched = true;
            }
            break;
        case ItemType2::Titan:
            levi.Die();
            al_play_sample_instance(oi);
            if (!item2.touched && levi.Stop()==2) {
                printf("touched");
                atk--;
                x += 350;
                item2.touched = true;
            }
            break;
    }
}

void Frame2::Draw() {
    for (const auto& item2 : items) {
        float drawX = x + item2.x;
        float drawY = item2.y;
        al_draw_bitmap(item2.bitmap, drawX, drawY, 0);
    }

    if (showDing && al_get_time() - dingStartTime <= dingDuration) {
        al_draw_bitmap(ding, dingX, dingY, 0);
    } else showDing = false;

    string life_text = to_string(life);
    string atk_text = to_string(atk);
    string tube_text = to_string(tube);
    al_draw_text(font, DARK, 180, 60, 0, life_text.c_str());
    al_draw_text(font, DARK, 445, 60, 0, atk_text.c_str());
    al_draw_text(font, DARK, 1470, 60, 0, tube_text.c_str());
    al_draw_text(font, DARK, 1520, 60, 0, "/10");
}

void Frame2::Ding(Levi& levi) {
    showDing = true;
    dingStartTime = al_get_time();
    dingX = levi.getX() -50;
    dingY = levi.getY() - 50;
    al_play_sample_instance(dingSound);
}

void Frame2::Destroy() {
    for (auto& item2 : items) {
        if (item2.bitmap) {
            al_destroy_bitmap(item2.bitmap);
        }
    }
    items.clear();
    al_destroy_timer(frame_timer);
    al_destroy_bitmap(ding);
    al_destroy_bitmap(key);
    al_destroy_sample_instance(dingSound);
    al_destroy_sample_instance(oi);
    al_destroy_sample_instance(hit);
    al_destroy_font(font);
}
