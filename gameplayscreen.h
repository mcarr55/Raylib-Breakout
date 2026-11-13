#ifndef GAMEPLAYSCREEN_H
#define GAMEPLAYSCREEN_H

#include "gamestate.h"

struct GamePlayScreen : GameState{

    using GameState::GameState;

    int score;

    int highScore;

    int numBlocksDestroyed;

    int lives;

    bool startGame;

    bool gameOver;

    float elaspedTime;

    float timeSinceStart;

    bool leaveTitleScreen;

    ScreenState currentScreen;

    int comboCounter;

    float accumulator;

    bool needToReset;

    void updatePlayer();
    void updateBall();
    void resetGameAfterLife();

    void resetGame();

    void update();
    void draw();
    void changeState();
};

#endif