#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *LeviMission = new GameWindow();
    LeviMission -> game_play();

    delete LeviMission;
    return 0;
}
