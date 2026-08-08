#include "raylib.h"


namespace Constants {
    constexpr float playerHorSpeed{ 200.0f };
    constexpr int blockWidth{80};
    constexpr int blockHeight{20};

}




//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

//enums for each screen state
typedef enum ScreenState { SCREEN_TEST, SCREEN_TITLE, SCREEN_GAMEPLAY, SCREEN_END } ScreenState;

typedef struct Player {
    Vector2 position;
    float speed;
} Player;

typedef struct Block{
    Rectangle rect;
    int blocking;
    Color color;
} Block;

typedef struct Ball{
    Vector2 position;
    int blocking;
    Color color;
    float x_speed;
    float y_speed;
} Ball;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

void updatePlayer(ScreenState* currentScreen, Player* player, float deltaTime);

//void updateBall(ScreenState* currentScreen, Ball* ball, float deltaTime);



int main(){

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "test");

    ScreenState currentScreen = SCREEN_TEST;

    Player player = { 0 };
    player.position = (Vector2){ 400, 400 };
    player.speed = 0;


    //8*4 = 32 blocks
    Block blockItems[32];


    for (int i = 0; i < 32; i++) {
        blockItems[i] = {{ 60.0f +(85.0f * (i % 8) ), ( 60.0f + (25.0f * (i / 8))), Constants::blockWidth, Constants::blockHeight}, 1, GRAY };     
    }

    /*
    Block blockItems[] = {
        {{100, 100, Constants::blockWidth, Constants::blockHeight}, 1, GRAY },
        {{ 250, 300, Constants::blockWidth, Constants::blockHeight}, 1, GRAY },
        {{ 650, 300, Constants::blockWidth, Constants::blockHeight}, 1, GRAY }
    };
    */

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second



    // Main game loop
    while (!WindowShouldClose()){   // Detect window close button or ESC key
        

        //update
        float deltaTime = GetFrameTime();
        updatePlayer(&currentScreen, &player, deltaTime);
        updateBall(&currentScreen, &ball, deltaTime);



        //draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("test window", 190, 200, 20, LIGHTGRAY);

            //blocks
            for (int i = 0; i < 32; i++) DrawRectangleRec(blockItems[i].rect, blockItems[i].color);

            //player

            Rectangle playerRect = { player.position.x - 52.5f, player.position.y - 15.0f, 100.0f, 15.0f };
            DrawRectangleRec(playerRect, RED);

            DrawCircleV(player.position, 5.0f, GOLD);

        EndDrawing();
    }

}


void updatePlayer(ScreenState* currentScreen, Player* player, float deltaTime){

    switch (*currentScreen){

        case SCREEN_TEST:{

            if (IsKeyDown(KEY_LEFT)){

               player->position.x -= Constants::playerHorSpeed * deltaTime ;
            }

            if (IsKeyDown(KEY_RIGHT)){
               player->position.x += Constants::playerHorSpeed * deltaTime;
            }

        } break;


        case SCREEN_TITLE: {



        } break;
           

        case SCREEN_GAMEPLAY: {



        } break;
           

        case SCREEN_END: {

        } break;


        default:
            break;
    }

   
}

void updateBall(ScreenState* currentScreen, Ball* ball, float deltaTime){

    switch (*currentScreen){

         case SCREEN_TEST:{

  

    } break;

     default:
        break;

    }
}