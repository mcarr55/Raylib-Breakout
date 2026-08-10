#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef enum ScreenState : int;

typedef struct Player {
    Vector2 position;
    float speed;
} Player;

void updatePlayer(Player* player, float deltaTime);

#endif