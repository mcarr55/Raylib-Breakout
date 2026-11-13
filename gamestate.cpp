#include "gamestate.h"

struct Game;

GameState::GameState(){

}

GameState::GameState(Game *parent){

    gameParent = parent;

}

GameState::~GameState(){

    gameParent = nullptr;

}



