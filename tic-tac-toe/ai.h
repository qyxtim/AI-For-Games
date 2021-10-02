#pragma once

#include "board.h"

class AI
{
public:
    Board b;

public:
    AI(char c);

    // This function uses AI to take a move
    void move();

private:
    // Minimax: return a bestMove for next round
    GridLocation minimax();

    // Core part of Minimax Algorithm
    int min(Board);
    int max(Board);
};