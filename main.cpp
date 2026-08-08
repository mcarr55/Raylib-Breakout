#include "raylib.h"
#include <cmath>
#include <iostream>

using namespace std;

namespace Constants {
    constexpr float playerHorSpeed{ 350.0f };
    constexpr int blockWidth{80};
    constexpr int blockHeight{20};


    constexpr float blockHorizontalOffset{ 82.5f };
    constexpr float blockVerticalOffset{25.0f};

    //declare fixed constants
    constexpr double FIXED_TIMESTEP = 1.0 / 60.0; // 0.016666 seconds
    constexpr double MAX_FRAME_TIME = 0.25;

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
    float radius;
} Ball;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------

void updatePlayer(ScreenState* currentScreen, Player* player, float deltaTime);

void updateBall(ScreenState* currentScreen, Ball* ball, float deltaTime, Block* blocks, Player* player);


int main(){

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "test");

    ScreenState currentScreen = SCREEN_TEST;

    Player player = { 0 };
    player.position = (Vector2){ 400, 400 };
    player.speed = Constants::playerHorSpeed;

    Ball ball = { 0 };
    ball.position = (Vector2){ 400, 300 };
    ball.x_speed = 300;
    ball.y_speed = -300;
    ball.radius = 10.0f;

    Vector2 prevBallPos = ball.position;


    //8*4 = 32 blocks
    Block blockItems[32];


    for (int i = 0; i < 32; i++) {
        blockItems[i] = {{ 60.0f +(Constants::blockHorizontalOffset * (i % 8) ), ( 60.0f + (Constants::blockVerticalOffset * (i / 8))), Constants::blockWidth, Constants::blockHeight}, 1, GRAY };
        blockItems[i].blocking = 1;     
    }

    /*
    Block blockItems[] = {
        {{100, 100, Constants::blockWidth, Constants::blockHeight}, 1, GRAY },
        {{ 250, 300, Constants::blockWidth, Constants::blockHeight}, 1, GRAY },
        {{ 650, 300, Constants::blockWidth, Constants::blockHeight}, 1, GRAY }
    };
    */

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second




    float accumulator = 0.0f;



    // Main game loop
    while (!WindowShouldClose()){   // Detect window close button or ESC key
        

        //update
        float deltaTime = GetFrameTime();


        if (deltaTime > 0.25f) deltaTime = 0.25f; // Cap spike to avoid death spiral
        accumulator += deltaTime;


        while (accumulator >= Constants::FIXED_TIMESTEP) {

            prevBallPos = ball.position;
            
            updateBall(&currentScreen, &ball, Constants::FIXED_TIMESTEP, blockItems, &player);

            updatePlayer(&currentScreen, &player, Constants::FIXED_TIMESTEP);


            accumulator -= Constants::FIXED_TIMESTEP;
        }

       
    
        //draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("test window", 190, 200, 20, LIGHTGRAY);

            //blocks
            for (int i = 0; i < 32; i++) {

                if (blockItems[i].blocking == 1){

                    DrawRectangleRec(blockItems[i].rect, blockItems[i].color);

                }
            }

            //player

            Rectangle playerRect = { player.position.x - 52.5f, player.position.y - 15.0f, 100.0f, 15.0f };
            DrawRectangleRec(playerRect, RED);

            DrawCircleV(player.position, 5.0f, GOLD);

            //Ball
            DrawCircleV(ball.position, ball.radius, BLUE);

            DrawFPS(10, 10);

        EndDrawing();
    }

}


void updatePlayer(ScreenState* currentScreen, Player* player, float deltaTime){

    switch (*currentScreen){

        case SCREEN_TEST:{

            if (IsKeyDown(KEY_LEFT)){

               player->position.x -= player -> speed * deltaTime ;
            }

            if (IsKeyDown(KEY_RIGHT)){
               player->position.x += player -> speed * deltaTime;
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

void updateBall(ScreenState* currentScreen, Ball* ball, float deltaTime, Block* blocks, Player* player){
    switch (*currentScreen){
        case SCREEN_TEST:{
           
            //move ball
            ball->position.x += ball->x_speed * deltaTime;
            ball->position.y += ball->y_speed * deltaTime;

            // collision with blocks
            for (int i = 0; i < 32; i++) {
                if (blocks[i].blocking == 0) continue;

                // define block bounds
                float blockLeft = 60.0f + (Constants::blockHorizontalOffset * (i % 8));
                float blockRight = blockLeft + Constants::blockWidth;
                float blockTop = 60.0f + (Constants::blockVerticalOffset * (i / 8));
                float blockBottom = blockTop + Constants::blockHeight;

                // Check AABB vs Circle Overlap
                if (ball->position.x + ball->radius >= blockLeft && 
                    ball->position.x - ball->radius <= blockRight &&
                    ball->position.y + ball->radius >= blockTop && 
                    ball->position.y - ball->radius <= blockBottom) {

                    blocks[i].blocking = 0;

                    // calculate overlap depths on both axes
                    float overlapLeft = (ball->position.x + ball->radius) - blockLeft;
                    float overlapRight = blockRight - (ball->position.x - ball->radius);
                    float overlapTop = (ball->position.y + ball->radius) - blockTop;
                    float overlapBottom = blockBottom - (ball->position.y - ball->radius);

                    float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
                    float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

                    // Resolve on the shallowest axis to determine face hit cleanly
                    if (minOverlapY < minOverlapX) {
                        if (overlapTop < overlapBottom) {
                            // Hit top face -> Force up, snap position outside
                            ball->y_speed = -abs(ball->y_speed);
                            ball->position.y = blockTop - ball->radius;
                        } else {
                            // Hit bottom face -> Force down, snap position outside
                            ball->y_speed = abs(ball->y_speed);
                            ball->position.y = blockBottom + ball->radius;
                        }
                    } else {
                        if (overlapLeft < overlapRight) {
                            // Hit left face -> Force left
                            ball->x_speed = -abs(ball->x_speed);
                            ball->position.x = blockLeft - ball->radius;
                        } else {

                            // hit right face -> Force right
                            ball->x_speed = abs(ball->x_speed);
                            ball->position.x = blockRight + ball->radius;
                        }
                    }
                    break;
                }
            }

            //player paddle collision
            float paddleLeft = player->position.x - 52.5f;
            float paddleRight = player->position.x + 52.5f;
            float paddleTop = player->position.y - 15.0f;
            float paddleBottom = player->position.y + 15.0f;

            if (ball->position.x + ball->radius >= paddleLeft && 
                ball->position.x - ball->radius <= paddleRight &&
                ball->position.y + ball->radius >= paddleTop && 
                ball->position.y - ball->radius <= paddleBottom) {

                // snap the ball directly on top of the paddle surface to break sticky cycles
                ball->position.y = paddleTop - ball->radius;

                // calculate relative hit position (-1.0 to 1.0)
                float relativeHit = (ball->position.x - player->position.x) / 52.5f;
                float bounceAngle = relativeHit * 75.0f;

                ball->x_speed = 335.0f * sin(bounceAngle * (PI / 180.0f));

                // force y_speed negative so it ALWAYS travels upwards (-Y)
                ball->y_speed = -abs(335.0f * cos(bounceAngle * (PI / 180.0f)));
            }

            //screen edge collision
            if (ball->position.x - ball->radius <= 0) {
                ball->x_speed = abs(ball->x_speed);
                ball->position.x = ball->radius;
            }   
            else if (ball->position.x + ball->radius >= 800) {
                ball->x_speed = -abs(ball->x_speed);
                ball->position.x = 800 - ball->radius;
            }

            if (ball->position.y - ball->radius <= 0) {
                ball->y_speed = abs(ball->y_speed);
                ball->position.y = ball->radius;
            }

            //falling off the bottom edge
            else if (ball->position.y + ball->radius >= 450) {
                ball->y_speed = -abs(ball->y_speed);
                ball->position.y = 450 - ball->radius;
            }

        } break;
        default:
            break;
    }
}
