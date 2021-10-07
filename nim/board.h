#pragma once

#include <set>

// Used to represent action (x, y)
// Take y from position x
struct Pair
{
    int x, y;
};

bool operator<(const Pair &a, const Pair &b);

class Nim
{

private:
    int *piles;
    int numberOfPiles;

    // 0 for first player, 1 for second player
    int player;

public:
    Nim(int, int);
    ~Nim();

    std::set<Pair> availableActions() const;

    // Need to validate the input
    bool remove(const Pair&);

    bool isEnd() const;

    void output() const;

    // Return who is the winner
    int winner() const;

    friend class AI;

private:
    Nim();
    inline void setPlayer();
};