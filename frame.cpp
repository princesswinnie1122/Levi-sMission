#include "frame.h"
#include "Levi.h"
#include "GameWindow.h"
#include <iostream>
#include <sstream>

#define WHITE al_map_rgb(255, 255, 255)
using namespace std;

Frame::Frame() : x(0), speed(0.8), isPaused(false), pauseDuration(0), currentPauseTime(0), preventUp(false), preventDown(false) {
}

void Frame::Init() {
    frame_timer = al_create_timer(1.0 / 60.0);
    al_start_timer(frame_timer);

    font = al_load_ttf_font("./fonts/PixelCombat.ttf",48,0);

    const ItemData itemData[] = {
        //bonus
        {"./images/tea.png", 3745, 730, ItemType::BlackTea, 55, 95, true, false},
        {"./images/tea.png", 1335+8000, 345, ItemType::BlackTea, 55, 95, true, false},
        {"./images/tea.png", 4385+8000, 480, ItemType::BlackTea, 55, 95, true, false},
        {"./images/tea.png", 5980+8000, 720, ItemType::BlackTea, 55, 95, true, false},
        {"./images/tea.png", 3700+16000, 455, ItemType::BlackTea, 55, 95, true, false},
        {"./images/tea.png", 6100, 435, ItemType::BlackTea, 55, 95, true, false},
        {"./images/tea.png", 110+8000, 575, ItemType::BlackTea, 55, 95, true, false},

        {"./images/broom.png", 2640+8000, 710, ItemType::Broom, 120, 125, true, false},
        {"./images/broom.png", 140+16000, 430, ItemType::Broom, 120, 125, true, false},
        {"./images/broom.png", 6990+16000, 610, ItemType::Broom, 120, 125, true, false},

        //oops
        {"./images/glass.png", 635+8000, 600, ItemType::BrokenGlass, 150, 70, true, false},
        {"./images/glass.png", 2510+8000, 340, ItemType::BrokenGlass, 150, 70, true, false},
        {"./images/glass.png", 6450+8000, 745, ItemType::BrokenGlass, 150, 70, true, false},
        {"./images/glass.png", 640+16000, 200, ItemType::BrokenGlass, 150, 70, true, false},
        {"./images/glass.png", 7335+16000, 620, ItemType::BrokenGlass, 150, 70, true, false},

        {"./images/socks.png", 4980, 330, ItemType::StinkySocks, 130, 90, true, false},
        {"./images/socks.png", 2400+8000, 830, ItemType::StinkySocks, 130, 90, true, false},
        {"./images/socks.png", 1465+16000, 845, ItemType::StinkySocks, 130, 90, true, false},
        {"./images/socks.png", 4790+16000, 845, ItemType::StinkySocks, 130, 90, true, false},

        //~8000
        {"./images/vanity.png", 3450, 150, ItemType::Obstacle, 275, 200, false, false},
        {"./images/cabinet.png", 4165, 500, ItemType::Obstacle, 200, 200, false, false},
        {"./images/mirror.png", 5110, 660, ItemType::Obstacle, 185, 130, false, false},
        {"./images/blanket.png", 5635, 500, ItemType::Obstacle, 230, 130, false, false},
        {"./images/bed.png", 6570, 420, ItemType::Obstacle, 360, 180, false, false},
        {"./images/light.png", 7130, 90, ItemType::Obstacle, 90, 130, false, false},
        {"./images/sofa_l.png", 7270, 630, ItemType::Obstacle, 460, 130, false, false},
        {"./images/books.png", 880+8000, 285, ItemType::Obstacle, 145, 130, false, false},
        {"./images/table.png", 2160+8000, 770, ItemType::Obstacle, 230, 130, false, false},
        {"./images/sofa_s.png", 1860+8000, 270, ItemType::Obstacle, 225, 130, false, false},
        {"./images/plants.png", 3000+8000, 480, ItemType::Obstacle, 65, 130, false, false},
        {"./images/chair.png", 3350+8000, 615, ItemType::Obstacle, 155, 130, false, false},

        //~16000
        {"./images/mirror.png", 3960+8000, 260, ItemType::Obstacle, 185, 180, false, false},
        {"./images/sofa_l.png", 5030+8000, 625, ItemType::Obstacle, 460, 130, false, false},
        {"./images/cabinet.png", 5920+8000, 630, ItemType::Obstacle, 200, 130, false, false},
        {"./images/vanity.png", 6700+8000, 290, ItemType::Obstacle, 275, 200, false, false},
        {"./images/refri.png", 550+16000, 550, ItemType::Obstacle, 330, 130, false, false},
        {"./images/bed.png", 1760+16000, 290, ItemType::Obstacle, 360, 180, false, false},
        {"./images/light.png", 2100+16000, 90, ItemType::Obstacle, 90, 130, false, false},
        {"./images/table.png", 2415+16000, 770, ItemType::Obstacle, 230, 130, false, false},
        {"./images/chair.png", 2720+16000, 610, ItemType::Obstacle, 155, 130, false, false},
        {"./images/blanket.png", 3290+16000, 370, ItemType::Obstacle, 230, 130, false, false},
        {"./images/books.png", 4940+16000, 410, ItemType::Obstacle, 145, 130, false, false},
        {"./images/plants.png", 3890+16000, 230, ItemType::Obstacle, 65, 130, false, false},
        {"./images/sofa_s.png", 4470+16000, 650, ItemType::Obstacle, 225, 130, false, false},
        {"./images/dog.png", 5360+16000, 290, ItemType::Obstacle, 197, 130, false, false},
        {"./images/cat.png", 5840+16000, 490, ItemType::Obstacle, 156, 130, false, false},
        {"./images/tree.png", 6070+16000, 360, ItemType::Obstacle, 300, 300, false, false},
        {"./images/snow.png", 6390+16000, 655, ItemType::Obstacle, 268, 200, false, false},
        {"./images/santa.png", 7590+16000, 0, ItemType::Obstacle, 238, 200, false, false},

        //aot characters
        {"./images/1.png", 1495+8000, 600, ItemType::Character, 130, 125, false, false},
        {"./images/2.png", 4100+16000, 480, ItemType::Character, 130, 125, false, false},
        {"./images/3.png", 4525, 355, ItemType::Character, 130, 125, false, false},
        {"./images/4.png", 4750+8000, 330, ItemType::Character, 130, 125, false, false},
        {"./images/5.png", 7000, 495, ItemType::Character, 130, 125, false, false},
        {"./images/6.png", 1000+16000, 680, ItemType::Character, 130, 125, false, false},
        {"./images/7.png", 7560+8000, 480, ItemType::Character, 130, 125, false, false},
    };

    for (const auto& data : itemData) {
        ALLEGRO_BITMAP* bitmap = al_load_bitmap(data.filePath);
        if (bitmap != nullptr) {
            Item item = {bitmap, data.x, data.y, data.type, data.width, data.height, data.collectible};
            items.push_back(item);
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
    al_set_sample_instance_gain(dingSound, 1.2) ;

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


void Frame::Update(Levi& levi) {

    if (levi.Stop()==0 && x >= -24000+1800 && !levi.Jump()){
        x -= speed;
    }

    if(x <= -24000+1800) levi.Continue();

    if(!levi.Jump() && x > -1600) al_draw_bitmap(key, 150, 500, 0);


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

        if(levi.getX() + levi.getWidth() > itemX && levi.getX() + levi.getWidth() < itemX+itemWidth &&
           levi.getY() < itemY + itemHeight && levi.getY() + levi.getHeight() > itemY){
            HandleCollision(*it, levi);
            if (it->collectible) {
                it = items.erase(it);
                if(it->type == ItemType::BlackTea || it->type == ItemType::Broom)
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

bool Frame::PreventUp() const{
    return preventUp;
}

bool Frame::PreventDown() const{
    return preventDown;
}

int Frame::getLife() const {
    return life;
}

int Frame::getAtk() const {
    return atk;
}

void Frame::HandleCollision(Item& item, Levi& levi) {
    switch (item.type) {
        case ItemType::BlackTea:
            life++;
            break;
        case ItemType::Broom:
            atk++;
            break;
        case ItemType::BrokenGlass:
        case ItemType::StinkySocks:
            life-=1;
            al_play_sample_instance(oi);
            break;
        case ItemType::Obstacle:
            levi.Die();
            al_play_sample_instance(hit);
            if (!item.touched && levi.Stop()==2) {
                life-=2;
                x += 350;
                item.touched = true;
            }
            break;
        case ItemType::Character:
            levi.Die();
            al_play_sample_instance(hit);
            if (!item.touched && levi.Stop()==2) {

                atk--;
                x += 350;
                item.touched = true;
            }
            break;
            break;
    }
}

void Frame::Draw() {
    for (const auto& item : items) {
        float drawX = x + item.x;
        float drawY = item.y;
        al_draw_bitmap(item.bitmap, drawX, drawY, 0);
    }

    if (showDing && al_get_time() - dingStartTime <= dingDuration) {
        al_draw_bitmap(ding, dingX, dingY, 0);
    } else showDing = false;

    string life_text = to_string(life);
    string atk_text = to_string(atk);
    al_draw_text(font, WHITE, 180, 60, 0, life_text.c_str());
    al_draw_text(font, WHITE, 445, 60, 0, atk_text.c_str());
}

void Frame::Ding(Levi& levi) {
    showDing = true;
    dingStartTime = al_get_time();
    dingX = levi.getX() -50;
    dingY = levi.getY() - 50;
    al_play_sample_instance(dingSound);
}

void Frame::Destroy() {
    for (auto& item : items) {
        if (item.bitmap) {
            al_destroy_bitmap(item.bitmap);
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
