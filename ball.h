#ifndef BALL_H
#define BALL_H

#include "raylib.h"
#include "constants.h"

struct Player;
struct Block;
struct GameInfo;
enum ScreenState : int;


typedef struct Ball{
    Vector2 position;
    int blocking;
    Color color;
    float x_speed;
    float y_speed;
    float radius;
} Ball;

void updateBall(GameInfo* GameInfo, Ball* ball, float deltaTime, Block* blocks, Player* player);

#endif // BALL_H