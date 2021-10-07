#pragma once

#include "board.h"
#include <map>
#include <vector>

struct State
{
    std::vector<int> currentPiles;
    Pair nextAction;
};

bool operator<(const State &a, const State &b);

class AI
{
public:
    Nim m;

public:
    AI(int, int);

    // Training based on q-learning
    void train();

    // AI makes a move
    void move();

private:
    // size of the piles
    int size;

    // Store the q value of the (piles, action) pair
    std::map<State, double> mp;

    // Store the Nim for the play
    Nim *mptr;

    // Max Training Iterations
    const int maxTraining = 50000;

    // Q(s, a) = old value estimate + alpha * (new value estimate - old value estimate)
    const double alpha = 0.5;
    const double epsilon = 0.1;

private:
    double future_estimate() const;

    std::vector<int> currentPilesInVectors() const;
    // Choose best action available
    Pair nextmove(bool);
};