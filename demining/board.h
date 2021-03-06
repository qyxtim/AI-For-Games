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
public:
    // If it doesn't click mine, the `clickMine` variable should stay at {-1, -1}
    GridLocation mineLoc = {-1, -1};

private:
    // number represents the number of mines near them. -1 means the location is a mine
    int **grid;
    std::set<GridLocation> taggedLocations;
    std::set<GridLocation> clickedLocations;

    // size of the grid
    int size;
    // ratio of mines in the grid
    const double factor = 0.1;

public:
    Board(int);
    ~Board();

    Board& operator=(const Board &);

    // output intermediate state
    void output() const;

    // output the entire board after the game ends
    void finaloutput() const;

    // insert location into taggedLocation, avoid futher clicking
    void tag(const GridLocation& location);

    // reset tagged location to normal status
    void reset(const GridLocation& location);

    // click certain place. if it is mine, it will insert that location to taggedLocation and clickedLocation
    void click(const GridLocation& location);

    // Check whether the game ends
    bool isEnd() const;

    bool clickMine() const;

    // Get the number of corresponding location
    int getMines(const GridLocation& location) const;

    friend class AI;
    friend void render(int, int, bool);
    friend void init();
    friend void onClick(int, int, int, int, void *);
};