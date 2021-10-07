#pragma once

#include <set>

struct GridLocation
{
    int x, y;
};

inline bool operator<(const GridLocation &lhs, const GridLocation &rhs)
{
    if (lhs.x != rhs.x)
        return lhs.x < rhs.x;
    return lhs.y < rhs.y;
}

class Board
{
private:
    int board[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
    std::set<GridLocation> availableActions;
    int currentPlay = 1; // Record who is currently playing
    char whoFirst;       // Record who plays the first. This is used to find who is the winner

public:
    Board(char c);
    Board(const Board &other);

    // Output the board
    void output() const;

    // If not successfully moved, return false.
    bool move(const GridLocation& location);

    // Check if the game is over.
    bool isEnd() const;

    // 0 for tie, 1 for user, -1 for AI (an utility function for AI)
    int winner() const;

    friend class AI;

private:
    // Get which symbol wins
    int winnerHelper() const;
};