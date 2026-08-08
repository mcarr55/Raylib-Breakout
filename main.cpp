#include "raylib.h"

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

//enums for each screen state
typedef enum { SCREEN_TITLE, SCREEN_GAMEPLAY, SCREEN_END } ScreenState;

typedef struct Player {
    Vector2 position;
    float speed;
    bool canJump;
} Player;

typedef struct Block{
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;


int main(){

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "test");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second



    // Main game loop
    while (!WindowShouldClose()){   // Detect window close button or ESC key
        

        //update

        //draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("test window", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

}