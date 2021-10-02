#include "ai.h"
#include <random>

AI::AI() : g(), maxSearchLength(5000), searchPerPath(20000)
{
}

bool AI::makeMove()
{
    double scores[4];
    for (int i = 0; i < 4; i++)
        scores[i] = 0;

    for (int i = 0; i < 4; i++)
    {
        Grid tmp = g;

        bool isSuccess = true;

        switch (i)
        {
        case 0:
            isSuccess = tmp.up();
            break;
        case 1:
            isSuccess = tmp.left();
            break;
        case 2:
            isSuccess = tmp.down();
            break;
        case 3:
            isSuccess = tmp.right();
            break;
        }

        if (!isSuccess)
            continue;

        scores[i] += tmp.score();

        for (int j = 0; j < searchPerPath; j++)
        {
            Grid searchBoard = tmp;
            searchBoard.generateAPlace();

            int height = maxSearchLength;
            while (make_random_move(searchBoard, height))
            {
                scores[i] += searchBoard.score();
                searchBoard.generateAPlace();
            }
        }
    }

    int pos = 0;
    for (int i = 1; i < 4; i++)
        if (scores[i] > scores[pos])
            pos = i;

    if (scores[pos] == 0)
        return false;

    switch (pos)
    {
    case 0:
        g.up();
        break;
    case 1:
        g.left();
        break;
    case 2:
        g.down();
        break;
    case 3:
        g.right();
        break;
    }
    g.generateAPlace();
    g.structure();

    return true;
}

bool AI::make_random_move(Grid &grid, int &searchlength)
{
    if (searchlength == 0)
        return false;

    int func = rand() % 4;
    bool isSuccess = true;

    switch (func)
    {
    case 0:
        isSuccess = grid.up();
        break;
    case 1:
        isSuccess = grid.left();
        break;
    case 2:
        isSuccess = grid.down();
        break;
    case 3:
        isSuccess = grid.right();
        break;
    }
    searchlength--;
    return isSuccess;
}