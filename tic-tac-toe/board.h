#pragma once

#include <set>

// Start: Define Grid and All the possible choices

struct GridLocation
{
    int x, y;
};

enum Choice
{
    Empty,
    X,
    O
};

// End

inline bool operator<(const GridLocation &lhs, const GridLocation &rhs)
{
    if (lhs.x != rhs.x)
        return lhs.x < rhs.x;
    return lhs.y < rhs.y;
}

class Board
{
private:
    Choice board[3][3] = {{Empty, Empty, Empty}, {Empty, Empty, Empty}, {Empty, Empty, Empty}};
    std::set<GridLocation> availableActions;
    Choice currentPlay = X; // Record current choice
    char whoFirst;       // Record who plays the first (x is the first). This is used to find who is the winner.

public:
    Board(char c);
    Board(const Board &other);

    // Output the board
    void output() const;

    // If not successfully moved, return false.
    bool move(const GridLocation &location);

    // Check if the game is over.
    bool isEnd() const;

    // 0 for tie, 1 for user, -1 for AI (an utility function for AI)
    // The winner is based on the user's perspective
    int winner() const;

    friend class AI;
    friend void onMouse(int evt, int x, int y, int flags, void* param);
    friend void render(Board* bptr);

private:
    // Get which symbol wins
    Choice winnerHelper() const;
};