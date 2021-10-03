#include "ai.h"
#include <random>

#define maxLevel 25

std::set<GridLocation> AI::locationsNearBlock(const GridLocation &g) const
{
    int x = g.x;
    int y = g.y;
    while (x % 3 != 0)
        x--;
    while (y % 3 != 0)
        y--;

    std::set<GridLocation> s;
    for (int i = x; i <= x + 2; i++)
    {
        for (int j = y; j <= y + 2; j++)
            s.insert({i, j});
    }

    return s;
}

AI::AI() : knowledges({}), b()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (b(i, j) != 0)
                continue;

            std::set<int> availableValues = {1, 2, 3, 4, 5, 6, 7, 8, 9};

            // Remove value in the 3*3 block
            std::set<GridLocation> nearBlock = locationsNearBlock({i, j});
            for (auto iter = nearBlock.begin(); iter != nearBlock.end(); iter++)
                if (b(iter->x, iter->y) != 0)
                    availableValues.erase(b(iter->x, iter->y));

            // Remove value in the same row
            for (int n = 0; n < 9; n++)
                if (b(i, n) != 0)
                    availableValues.erase(b(i, n));

            // Remove value in the same col
            for (int m = 0; m < 9; m++)
                if (b(m, j) != 0)
                    availableValues.erase(b(m, j));

            knowledges.insert({{i, j}, availableValues});
        }
    }
}

bool AI::isEnded(const GridLocation &g) const
{
    std::set<GridLocation> nearBlock = locationsNearBlock(g);
    nearBlock.erase(g);

    for (auto iter = nearBlock.begin(); iter != nearBlock.end(); iter++)
        if (b(iter->x, iter->y) == b(g.x, g.y))
            return true;

    for (int i = 0; i < 9; i++)
        if (i != g.x && b(i, g.y) == b(g.x, g.y))
            return true;

    for (int n = 0; n < 9; n++)
        if (n != g.y && b(g.x, n) == b(g.x, g.y))
            return true;

    return false;
}

bool AI::solveHelper(int offset)
{
    if (offset == knowledges.size())
        return true;

    auto iter = knowledges.begin();
    std::advance(iter, offset);

    for (auto it = iter->possibleValues.begin(); it != iter->possibleValues.end(); it++)
    {
        b(iter->location.x, iter->location.y) = *it;
        if (!isEnded({iter->location.x, iter->location.y}) && solveHelper(offset + 1))
            return true;
        b(iter->location.x, iter->location.y) = 0;
    }

    return false;
}

bool AI::solve()
{
    return solveHelper(0);
}

void AI::buildHelper(int level, std::set<int> &availableOffset)
{
    if (level == maxLevel)
        return;

    int randindex = rand() % availableOffset.size();
    auto iterOffset = availableOffset.begin();
    std::advance(iterOffset, randindex);

    int offset = *iterOffset;
    auto iter = knowledges.begin();
    std::advance(iter, offset);

    availableOffset.erase(offset);

    for (auto it = iter->possibleValues.begin(); it != iter->possibleValues.end(); ++it)
    {
        b(iter->location.x, iter->location.y) = *it;
        if (!isEnded(iter->location))
        {
            return buildHelper(level + 1, availableOffset);
        }
        b(iter->location.x, iter->location.y) = 0;
    }

    availableOffset.insert(offset);
}

void AI::build()
{
    std::set<int> availableOffset;
    for (int i = 0; i < knowledges.size(); i++)
        availableOffset.insert(i);
    buildHelper(0, availableOffset);
}