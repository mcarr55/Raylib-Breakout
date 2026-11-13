#include "titlescreen.h"
#include "raylib.h"

TitleScreen::TitleScreen(){

    leaveTitleScreen = false;

    timeSinceStart = 0.0f;
}



void TitleScreen::update(){

    //switch to next screen after enough time
    if (leaveTitleScreen == true) {

        timeSinceStart += GetFrameTime()*10;
    }

    if (timeSinceStart >= 10.0f) {

        //gameInfo -> currentScreen = SCREEN_GAMEPLAY;
    }

    //indicate button is pressed
    if (IsKeyPressed(KEY_ENTER)) {

        leaveTitleScreen = true;
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


