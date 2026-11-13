#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "gamestate.h"

struct TitleScreen : GameState{

    bool leaveTitleScreen;

    float timeSinceStart;

    void update();

    void draw();

    void changeState();

    TitleScreen();

};

#endif