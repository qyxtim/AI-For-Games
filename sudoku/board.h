#pragma once

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
    int grid[9][9];

public:
    Board();

    // Overload operator () to allow grammar (i, j) to access grid[i][j]
    int &operator()(int x, int y);
    const int &operator()(int x, int y) const;

    // Output function of the grid
    void output() const;

    friend class Controller;
};