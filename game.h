#ifndef GAME_H
#define GAME_H

struct GameState;


struct Game{
    
    GameState* currentState;

    void startGame();

    void runGame();

    void changeState();

    Game();

    ~Game();

};

#endif