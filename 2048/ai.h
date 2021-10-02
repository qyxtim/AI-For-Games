#pragma once

#include "2048grid.h"

class AI
{
public:
    AI();
    bool makeMove();
    Grid g;

private:
    // Control the maximum length of search
    int maxSearchLength;
    // Control the number of loops for Monte Carlo tree search (MCTS)
    int searchPerPath;

    bool make_random_move(Grid &grid, int &searchlength);
};