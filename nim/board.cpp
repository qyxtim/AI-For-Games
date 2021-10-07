#include "board.h"
#include <cstdio>
#include <random>

bool operator<(const Pair &a, const Pair &b)
{
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

// Only can be used by Nim and its friend class(AI)
Nim::Nim() : numberOfPiles(0)
{
}

Nim::Nim(int size, int whoPlayFirst) : numberOfPiles(size), player(whoPlayFirst)
{
    piles = new int[size];
    for (int i = 0; i < size; i++)
        piles[i] = 1 + rand() % (2 * size - 1);
}

Nim::~Nim()
{
    delete[] piles;
}

inline void Nim::setPlayer()
{
    player = !player;
}

std::set<Pair> Nim::availableActions() const
{
    std::set<Pair> result;

    // Have to take at least one and only from one pile
    for (int i = 0; i < numberOfPiles; i++)
    {
        for (int j = 1; j <= piles[i]; j++)
            result.insert({i, j});
    }

    return result;
}

bool Nim::remove(const Pair &pair)
{
    if (pair.x < 0 || pair.x >= numberOfPiles)
        return false;

    if (pair.y <= 0 || pair.y > piles[pair.x])
        return false;

    piles[pair.x] -= pair.y;
    setPlayer();

    return true;
}

bool Nim::isEnd() const
{
    for (int i = 0; i < numberOfPiles; i++)
    {
        if (piles[i] != 0)
            return false;
    }
    return true;
}

// Negate because !player is the one who take previous action
int Nim::winner() const
{
    if (!isEnd())
        return -1;
    return player;
}

void Nim::output() const
{
    for (int i = 0; i < numberOfPiles; i++)
        printf("%d ", piles[i]);
    printf("\n");
}