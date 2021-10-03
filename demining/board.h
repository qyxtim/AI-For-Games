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
    // size of the grid
    int size;
    // ratio of mines in the grid
    const double factor = 0.1;

public:
    Board(int);
    ~Board();

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

    // Get the number of corresponding location
    int getMines(const GridLocation& location) const;

    // return the intersection of taggedLocation and clickedLocation
    std::set<GridLocation> intersections() const;

private:
    // number represents the number of mines near them. -1 means the location is a mine
    int **grid;
    std::set<GridLocation> taggedLocations;
    std::set<GridLocation> clickedLocations;
};