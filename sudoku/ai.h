#pragma once

#include "board.h"
#include <set>

struct Knowledge
{
    GridLocation location;
    std::set<int> possibleValues;
};

inline bool operator<(const Knowledge &lhs, const Knowledge &rhs)
{
    if (lhs.possibleValues.size() != rhs.possibleValues.size())
        return lhs.possibleValues.size() < rhs.possibleValues.size();
    return lhs.location < rhs.location;
}

class AI
{
private:
    std::set<Knowledge> knowledges;

private:
    std::set<GridLocation> locationsNearBlock(const GridLocation &) const;

    // Check whether the new updated location makes it impossible to solve sudoku
    bool isEnded(const GridLocation &) const;

    // Helper function to solve sudoku
    bool solveHelper(int);

    // Helper function to help build sudoku
    void buildHelper(int, std::set<int> &availableOffset);

    void updateKnowledge();

public:
    Board b;

public:
    // This function solves the sudoku by using backtracking.
    // It returns False if the sudoku has no solution.
    bool solve();

    // This function is used to build sudoku
    void build();

    friend class Controller;
};