#include "game.h"
#include "raylib.h"

#include "gamestate.h"
struct GameState;


#include "titlescreen.h"
struct TitleScreen;

#include <stdio.h>


Game::Game(){
    
    currentState = new struct TitleScreen(this);

}

Game::~Game(){

    if (currentState != nullptr){

        delete currentState;
        currentState = nullptr;

    }

}


void Game::startGame(){

    runGame();
}

void Game::runGame(){

    //run game
    while (!WindowShouldClose()){   // Detect window close button or ESC key

        if (currentState != nullptr){

            currentState -> update();

            currentState -> draw();

        }    
    }
}


void Game::changeState(GameState* newState){

    if (currentState != nullptr){

        printf("about to delete current state\n");

        delete currentState;

        printf("deleted state\n");


        currentState = nullptr;

    }

    currentState = newState;

    printf("swapped\n");

}