#include "raylib.h"
#include <cmath>
#include <iostream>

#include "block.h"
#include "player.h"
#include "ball.h"
#include "gameInfo.h"

using namespace std;

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

//enums for each screen state
typedef enum ScreenState : int { SCREEN_TEST, SCREEN_TITLE, SCREEN_GAMEPLAY, SCREEN_END} ScreenState;


//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

void resetGameAfterLife(Player* player, Ball* ball);


void update(GameInfo* gameInfo, Player* player, Ball* ball, Block* blocks);

void updateTitle(GameInfo* gameInfo);

void updateGame(GameInfo* gameInfo, Player* player, Ball* ball, Block* blocks);

void updateEnd(GameInfo* gameInfo);



void draw(GameInfo* gameInfo, Player* player, Ball* ball, Block* blocks);

void drawTitle(GameInfo* gameInfo);

void drawGame(GameInfo* gameInfo, Player* player, Ball* ball, Block* blocks);

void drawEnd(GameInfo* gameInfo);


int main(){

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

   
    InitWindow(screenWidth, screenHeight, "raylib breakout game");

    GameInfo gameInfo = {0};
    gameInfo.score = 0;
    gameInfo.highScore = 0;
    gameInfo.numBlocksDestroyed = 0;
    gameInfo.lives = 3;
    gameInfo.startGame = false;
    gameInfo.gameOver = false;
    gameInfo.elaspedTime = 0.0f;
    gameInfo.timeSinceStart = 0.0f;
    gameInfo.leaveTitleScreen = false;
    gameInfo.currentScreen = SCREEN_TITLE;
    gameInfo.comboCounter = 0;
    gameInfo.accumulator = 0;

    gameInfo.needToReset = false;

    Player player = { 0 };
    player.position = (Vector2){ 400, 400 };
    player.speed = Constants::playerHorSpeed;

    Ball ball = { 0 };
    ball.position = (Vector2){ 400, 300 };
    ball.x_speed = 300;
    ball.y_speed = -300;
    ball.radius = 10.0f;


    //8 block per row, with 4 row = 32 blocks
    Block blockItems[Constants::numBlocks];


    for (int i = 0; i < Constants::numBlocks; i++) {
        blockItems[i] = {{ 60.0f +(Constants::blockHorizontalOffset * (i % 8) ), ( 60.0f + (Constants::blockVerticalOffset * (i / 8))), Constants::blockWidth, Constants::blockHeight}, 1, GRAY };
        blockItems[i].blocking = 1;     
    }

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()){   // Detect window close button or ESC key

        update(&gameInfo, &player, &ball, blockItems);

        draw(&gameInfo, &player, &ball, blockItems);
    }

}



void resetGame(Player* player, Ball* ball, Block* blocks, GameInfo* gameInfo) {
    // Reset player position
    player->position = (Vector2){ 400, 400 };

    // Reset ball position and speed
    ball->position = (Vector2){ 400, 300 };
    ball->x_speed = 300;
    ball->y_speed = -300;

    // Reset blocks
    for (int i = 0; i < Constants::numBlocks; i++) {
        blocks[i] = { { 60.0f + (Constants::blockHorizontalOffset * (i % 8)), 
                        60.0f + (Constants::blockVerticalOffset * (i / 8)), 
                        Constants::blockWidth, 
                        Constants::blockHeight }, 
                      1, GRAY };
    }

    // Reset score and lives
    gameInfo -> score = 0;
    gameInfo -> numBlocksDestroyed = 0;
    gameInfo -> lives = 3;
}

void resetGameAfterLife(Player* player, Ball* ball, GameInfo* gameInfo) {

    gameInfo -> needToReset = false;


    gameInfo -> score =  gameInfo -> score / 2;

    gameInfo -> elaspedTime = 0.0f;

    gameInfo -> comboCounter = 0;

    // Decrease lives
    gameInfo -> lives--;


      if (gameInfo -> lives <= 0) {
        // Game over logic
        gameInfo -> gameOver = true;
        gameInfo -> currentScreen = SCREEN_END;
    }

    // Reset player position
    player->position = (Vector2){ 400, 400 };

    // Reset ball position and speed
    ball->position = (Vector2){ 400, 300 };
    ball->x_speed = 300;
    ball->y_speed = -300;


    gameInfo -> startGame = false;

    gameInfo -> needToReset = false;
}


void update(GameInfo* gameInfo, Player* player, Ball* ball, Block* blocks){

    switch (gameInfo->currentScreen){

        case SCREEN_TITLE: { 

            updateTitle(gameInfo);
            
        } break;

        case SCREEN_GAMEPLAY: {  

            updateGame(gameInfo, player, ball, blocks);

        } break;

        case SCREEN_END: {  

            updateEnd(gameInfo);

        } break;

         default:
            break;
    }

}

void draw(GameInfo* gameInfo, Player* player, Ball* ball, Block* blocks){

    switch (gameInfo->currentScreen){

        case SCREEN_TITLE: { 

            drawTitle(gameInfo);
            
        } break;

        case SCREEN_GAMEPLAY: {  

            drawGame(gameInfo, player, ball, blocks);

        } break;

        case SCREEN_END: {  

            drawEnd(gameInfo);

        } break;

         default:
            break;
    }

}


void updateTitle(GameInfo *gameInfo){

    //switch to next screen after enough time
    if (gameInfo -> leaveTitleScreen == true) {

        gameInfo -> timeSinceStart += GetFrameTime()*10;
    }

    if (gameInfo -> timeSinceStart >= 10.0f) {

        gameInfo -> currentScreen = SCREEN_GAMEPLAY;
    }

    //indicate button is pressed
    if (IsKeyPressed(KEY_ENTER)) {

        gameInfo -> leaveTitleScreen = true;
    }

}



void updateGame(GameInfo* gameInfo, Player* player, Ball* ball, Block* blocks){

    gameInfo -> leaveTitleScreen = false;

    //update
    float deltaTime = GetFrameTime();

    if (gameInfo -> startGame == false) {

        gameInfo -> elaspedTime += deltaTime;

        if (gameInfo -> elaspedTime >= 3.0f){

            gameInfo -> startGame = true;

        }
    }

    else {

        //accumulator logic for fixed timestep
        if (deltaTime > 0.25f) deltaTime = 0.25f; // Cap spike to avoid death spiral
        gameInfo -> accumulator += deltaTime;
                    

        while (gameInfo -> accumulator >= Constants::FIXED_TIMESTEP) {

            //prevBallPos = ball.position;
                        
            updateBall(gameInfo, ball, Constants::FIXED_TIMESTEP, blocks, player);

            if (gameInfo -> needToReset == true){

                resetGameAfterLife(player, ball, gameInfo);

            }

            updatePlayer(player, Constants::FIXED_TIMESTEP);


            gameInfo -> accumulator -= Constants::FIXED_TIMESTEP;
        }


    }
                
    if (gameInfo -> numBlocksDestroyed == Constants::numBlocks) {
       
        gameInfo -> currentScreen = SCREEN_END;
                        
    }

}


void updateEnd(GameInfo* gameInfo){

}






void drawTitle(GameInfo *gameInfo){

    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Breakout Game", 95, 170, 80, LIGHTGRAY);

        if( (int(gameInfo -> timeSinceStart) % 2) == 0) {

            DrawText("Press Enter to Start", 300, 250, 20, LIGHTGRAY);
        }
                
    EndDrawing();

}




void drawGame(GameInfo* gameInfo, Player* player, Ball* ball, Block* blocks){

    BeginDrawing();

        ClearBackground(RAYWHITE);

        //blocks
        for (int i = 0; i < Constants::numBlocks; i++) {

            if (blocks[i].blocking == 1){

                DrawRectangleRec(blocks[i].rect, blocks[i].color);

            }
        }

        //player

        Rectangle playerRect = { (player -> position.x) - 52.5f, (player -> position.y) - 15.0f, 100.0f, 15.0f };
        DrawRectangleRec(playerRect, RED);

        //Ball
        DrawCircleV(ball -> position, ball -> radius, BLUE);

        DrawText(TextFormat("Score: %d", gameInfo -> score), 10, 10, 20, BLACK);
        DrawText(TextFormat("High Score: %d", gameInfo -> highScore), 10, 30, 20, BLACK);
        DrawText(TextFormat("Lives: %d", gameInfo -> lives), 700, 10, 20, BLACK);
        DrawText(TextFormat("Combo: %d", gameInfo -> comboCounter), 700, 30, 20, BLACK);

        //DrawFPS(700, 50);

        //cout << "number of blocks destroyed: " << numBlocksDestroyed << endl;


        if (gameInfo -> startGame == false) {

            if (gameInfo -> elaspedTime >= 3.0f) {

                DrawText("Start", 400, 200, 40, BLACK);
                            
            }

            else if (gameInfo -> elaspedTime >= 2.0f) {

                DrawText("1", 400, 200, 40, BLACK);
                            
            }

            else if (gameInfo -> elaspedTime >= 1.0f) {
                            
                DrawText("2", 400, 200, 40, BLACK);

            }

            else if (gameInfo -> elaspedTime >= 0.0f) {

                DrawText("3", 400, 200, 40, BLACK);
                            
                }    
        }

        EndDrawing();
}



void drawEnd(GameInfo* gameInfo){

    BeginDrawing();
                    
        ClearBackground(RAYWHITE);

        DrawText("Game Over", 300, 200, 40, BLACK);
        DrawText(TextFormat("Final Score: %d", gameInfo -> score), 300, 250, 20, BLACK);
        DrawText(TextFormat("High Score: %d", gameInfo -> highScore), 300, 280, 20, BLACK);

    EndDrawing();

}