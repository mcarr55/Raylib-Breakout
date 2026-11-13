#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "game.h"

enum ScreenState : int;


struct GameState{

    ScreenState currentScreen;

    Game* gameParent;

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void changeState() = 0;

    GameState();

    GameState(Game* parent);

    virtual ~GameState();

};

struct EndScreen : GameState{

    ScreenState currentScreen;

    void update();

    void draw();

};

#endif