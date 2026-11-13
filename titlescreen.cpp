#include "titlescreen.h"
#include "raylib.h"


#include "game.h"
struct Game;

#include "gameplayscreen.h"
struct GamePlayScreen;


TitleScreen::TitleScreen(){

    leaveTitleScreen = false;

    timeSinceStart = 0.0f;
}



void TitleScreen::update(){

    //switch to next screen after enough time
    if (leaveTitleScreen == true) {

        timeSinceStart += GetFrameTime()*10;
    }

    //indicate button is pressed
    if (IsKeyPressed(KEY_ENTER)) {

        leaveTitleScreen = true;
    }

    if (timeSinceStart >= 10.0f) {

        gameParent -> changeState(new struct GamePlayScreen(gameParent));

        return;
    }

}

void TitleScreen::draw(){

    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Breakout Game", 95, 170, 80, LIGHTGRAY);

        if( (int(timeSinceStart) % 2) == 0) {

            DrawText("Press Enter to Start", 300, 250, 20, LIGHTGRAY);
        }
                
    EndDrawing();
}

void TitleScreen::changeState(){

} 


