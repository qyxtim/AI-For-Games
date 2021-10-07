#include "ai.h"
#include <cstdio>
#include <random>

bool operator<(const State &a, const State &b)
{
    for (int i = 0; i != a.currentPiles.size(); ++i)
        if (a.currentPiles[i] != b.currentPiles[i])
            return a.currentPiles[i] < b.currentPiles[i];

    if (a.nextAction.x != b.nextAction.x)
        return a.nextAction.x < b.nextAction.x;
    return a.nextAction.y < b.nextAction.y;
}

AI::AI(int size, int whoPlayFirst) : size(size), mp({})
{
    mptr = new Nim(size, whoPlayFirst);
}

double AI::future_estimate() const
{
    std::set<Pair> availableActions = m.availableActions();
    std::vector<int> currentPiles = currentPilesInVectors();

    double utility = -2;

    for (auto action = availableActions.begin(); action != availableActions.end(); ++action)
    {
        auto iter = mp.find({currentPiles, *action});
        if (iter != mp.end())
            utility = iter->second > utility ? iter->second : utility;
    }

    utility = (utility == -2) ? 0 : utility;

    return utility;
}

std::vector<int> AI::currentPilesInVectors() const
{
    std::vector<int> currentPiles;

    for (int i = 0; i < size; i++)
        currentPiles.push_back(m.piles[i]);

    return currentPiles;
}

Pair AI::nextmove(bool isTraining = true)
{
    std::set<Pair> availableActions = m.availableActions();

    // Epsilon Greedy Algorithm - try to explore new actions
    if (isTraining && double(rand()) / RAND_MAX > epsilon)
    {
        auto iter = availableActions.begin();
        std::advance(iter, rand() % availableActions.size());
        return *iter;
    }

    // Find the action with largest q value
    std::vector<int> currentPiles = currentPilesInVectors();
    Pair returnedAction = {-1, -1};
    double utility = -2;
    for (auto action = availableActions.begin(); action != availableActions.end(); ++action)
    {
        auto iter = mp.find({currentPiles, *action});
        if (iter == mp.end())
        {
            if (returnedAction.x == -1)
                returnedAction = *action;
        }
        else
        {
            if (iter->second > utility)
            {
                utility = iter->second;
                returnedAction = *action;
            }
        }
    }

    return returnedAction;
}

void AI::train()
{
    Nim *mtrain;

    for (int i = 0; i < maxTraining; i++)
    {
        printf("AI trains %d time!\n", i + 1);

        mtrain = new Nim(size, rand() % 2);
        m = *mtrain;
        State lastState[2] = {{{}, {-1, -1}}, {{}, {-1, -1}}};

        while (!m.isEnd())
        {
            Pair nextMove = nextmove();
            std::vector<int> currentPiles = currentPilesInVectors();
            lastState[m.player] = {currentPiles, nextMove};

            m.remove(nextMove);

            // For states like: State1 --> State2 --> State3, State 1's future estimate is only affected by State3
            if (!m.isEnd() && lastState[m.player].currentPiles.size() != 0)
                mp[lastState[m.player]] = mp[lastState[m.player]] + alpha * (future_estimate() - mp[lastState[m.player]]);
        }

        mp[lastState[!m.winner()]] = mp[lastState[!m.winner()]] + alpha * (-1 + future_estimate() - mp[lastState[!m.winner()]]);
        mp[lastState[m.winner()]] = mp[lastState[m.winner()]] + alpha * (1 + future_estimate() - mp[lastState[m.winner()]]);

        delete mtrain;
    }

    m = *mptr;
}

void AI::move()
{
    Pair nextMove = nextmove(false);
    printf("AI moves %d from %d\n", nextMove.y, nextMove.x);
    m.remove(nextMove);
}