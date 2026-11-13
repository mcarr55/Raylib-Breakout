#include "game.h"
#include "raylib.h"

#include "gamestate.h"
struct GameState;


#include "titlescreen.h"
struct TitleScreen;


Game::Game(){
    
    currentState = new struct TitleScreen();

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



/*

// Switch to a different subclass:
delete currentTask;
currentTask = new LoggingTask();
currentTask->execute();

delete currentTask; // Clean up

*/