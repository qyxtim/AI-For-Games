#pragma once

#include <set>

using namespace std;

struct GridLocation
{
	int x;
	int y;
};

// Have to provide a reload of the operator to help set
inline bool operator<(const GridLocation &lhs, const GridLocation &rhs)
{
	if (lhs.x != rhs.x)
		return lhs.x < rhs.x;
	return lhs.y < rhs.y;
}

class Grid
{
public:
	// Creates a new 2048 Grid.
	Grid();

	// Allow copy of 2048 Grid.
	Grid(const Grid &other);

	// This function moves all squares to left when user press 'A' or 'a'
	bool left();

	// This function moves all squares to right when user press 'D' or 'd'
	bool right();

	// This function moves all squares upward when user press 'W' or 'w'
	bool up();

	// This function moves all squares downward when user press 'S' or 's'
	bool down();

	// This function is used to output the grid.
	void structure() const;

	// This function is used to determine the score of the grid
	double score() const;

	// A helper function to generate a place to insert the number 2/4
	void generateAPlace();

	friend void render();

private:
	// 2D array that stores the grid
	int grid[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

	// A set that stores all the available place
	set<GridLocation> gl;

	inline void deleteGridLocation(int, int);
};
