#pragma once

#include "board.h"
#include <set>

struct Knowledge
{
    std::set<GridLocation> locations;
    int numberOfMines;
};

inline bool operator<(const Knowledge &lhs, const Knowledge &rhs)
{
    if (lhs.locations.size() != rhs.locations.size())
        return lhs.locations.size() < rhs.locations.size();
    return lhs.numberOfMines < rhs.numberOfMines;
}

class AI
{
public:
    AI(int);
    Board b;

    // Ask AI to take a move
    void move();

private:
    // If there is no known safety place, the AI will take a random move
    void makeRandomMove();

    // Based on existing knowledge, AI will make induction (based on subset)
    void makeInduction();

    // Update Knowledge about the board: update knownSafetyPlace, availableActions, dangerousPlace
    void updateKnowledge();

    // Check if small-sized set is a subset of large-sized set
    bool isSubset(const Knowledge &a, const Knowledge &b) const;

private:
    // Store the availableActions
    std::set<GridLocation> availableActions;

    // Store known Safety Place
    std::set<GridLocation> knownSafetyPlace;

    // Store known Dangerous Place
    std::set<GridLocation> dangerousPlace;

    // Store Knowledge abou the board
    std::set<Knowledge> knowledges;
};