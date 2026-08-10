#include "ball.h"
#include "block.h"
#include "player.h"
#include "constants.h"
#include "gameInfo.h"

#include "raylib.h"

#include <cmath>



void updateBall(GameInfo* gameInfo, Ball* ball, float deltaTime, Block* blocks, Player* player){

    //move ball
    ball->position.x += ball->x_speed * deltaTime;
    ball->position.y += ball->y_speed * deltaTime;

    // collision with blocks
    for (int i = 0; i < Constants::numBlocks; i++) {
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

            (gameInfo -> numBlocksDestroyed)++;

            gameInfo -> comboCounter++;

            gameInfo -> score += 1000*(gameInfo -> comboCounter) + 1;
            if ((gameInfo -> score) > (gameInfo -> highScore)) {
                gameInfo -> highScore = gameInfo -> score;
            }

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

        ball->x_speed = 350.0f * sin(bounceAngle * (PI / 180.0f));

        // force y_speed negative so it always travels upwards (-Y)
        ball->y_speed = -abs(350.0f * cos(bounceAngle * (PI / 180.0f)));

        if (abs(ball-> y_speed) < 200.0f) {
            ball->y_speed = -200.0f;
        }

        gameInfo -> comboCounter = 0;

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

        gameInfo -> needToReset = true;

        //resetGameAfterLife(player, ball);
                
    }

}