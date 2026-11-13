#ifndef GAMESTATE_H
#define GAMESTATE_H

enum ScreenState : int;


struct GameState{

    ScreenState currentScreen;

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void changeState() = 0;

};





struct GameScreen : GameState{

    
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
    
};

struct EndScreen : GameState{

    ScreenState currentScreen;

    void update();

    void draw();

};

#endif