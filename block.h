#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"

typedef struct Block{
    Rectangle rect;
    int blocking;
    Color color;
} Block;

#endif // BLOCK_H