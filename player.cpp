#include "player.h"
#include "raylib.h"

void updatePlayer(Player* player, float deltaTime){

            if (IsKeyDown(KEY_LEFT)) {
                player->position.x -= player->speed * deltaTime;
            }

            if (IsKeyDown(KEY_RIGHT)) {
                player->position.x += player->speed * deltaTime;
            }

            //prevent them from corossing sreeen border
            if (player->position.x - 52.5f < 0.0f) {
                player->position.x = 52.5f; 
            }

            if (player->position.x + 52.5f > 800.0f) {
                player->position.x = 800.0f - 52.5f;
            }
}