#ifndef GAMEINFO_H
#define GAMEINFO_H

enum ScreenState : int;

typedef struct GameInfo {
    
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

} GameInfo;

#endif