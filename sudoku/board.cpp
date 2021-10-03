#include "board.h"
#include <cstdio>

Board::Board()
{
    grid = new int *[9];
    for (int i = 0; i < 9; i++)
        grid[i] = new int[9];

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            grid[i][j] = 0;
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < 9; i++)
        delete[] grid[i];
    delete[] grid;
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
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}