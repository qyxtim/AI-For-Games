#include "board.h"
#include <cstdio>

Board::Board()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            grid[i][j] = 0;
    }
}

int &Board::operator()(int x, int y)
{
    return grid[x][y];
}

const int &Board::operator()(int x, int y) const
{
    return grid[x][y];
}

void Board::output() const
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            printf("%d ", grid[i][j]);
        printf("\n");
    }
}