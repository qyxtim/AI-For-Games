#include "2048grid.h"
#include <cstdio>
#include <cstring>
#include <random>

Grid::Grid() : gl({})
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			gl.insert({i, j});

	int built = 0;

	while (built < 2)
	{
		int x = rand() % 4;
		int y = rand() % 4;
		if (grid[x][y] == 0)
		{
			grid[x][y] = rand() % 2 == 0 ? 2 : 4;
			built += 1;
			deleteGridLocation(x, y);
		}
	}
}

Grid::Grid(const Grid &other) : gl{other.gl}
{
	memcpy(grid, other.grid, sizeof(other.grid));
}

inline void Grid::deleteGridLocation(int i, int k)
{
	gl.erase({i, k});
}

void Grid::generateAPlace()
{
	int index = -1;

	if (gl.size() != 0)
		index = rand() % gl.size();
	else
		return;

	auto iter = gl.begin();
	std::advance(iter, index);

	grid[iter->x][iter->y] = rand() % 2 == 0 ? 2 : 4;
	deleteGridLocation(iter->x, iter->y);
}

void Grid::structure() const
{
	printf("\n");
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			std::string s = std::to_string(grid[i][j]);
			for (unsigned int i = 0; i < 5 - s.length(); ++i)
				printf(" ");
			printf("%s", s.c_str());
		}
		printf("\n");
	}
	printf("\n");
}

double Grid::score() const
{
	int totalScore = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			totalScore += grid[i][j] * grid[i][j];
	}
	return (totalScore) + double(totalScore) / double(16 - gl.size()) * gl.size();
}

bool Grid::left()
{
	bool effectiveMove = false;

	for (int i = 0; i < 4; ++i)
	{
		int previous = -1;
		int pos = 0;
		int new_row[4] = {0, 0, 0, 0};
		for (int j = 0; j < 4; j++)
		{
			deleteGridLocation(i, j);
			if (grid[i][j] != 0)
			{
				if (previous == -1)
					previous = grid[i][j];
				else
				{
					if (grid[i][j] == previous)
					{
						new_row[pos++] = previous * 2;
						previous = -1;
					}
					else
					{
						new_row[pos++] = previous;
						previous = grid[i][j];
					}
				}
			}
		}
		if (previous != -1)
			new_row[pos] = previous;
		for (int j = 0; j < 4; j++)
		{
			if (new_row[j] == 0)
				gl.insert({i, j});
			if (new_row[j] != grid[i][j])
				effectiveMove = true;
			grid[i][j] = new_row[j];
		}
	}

	return effectiveMove;
}

bool Grid::up()
{
	bool effectiveMove = false;

	for (int k = 0; k < 4; ++k)
	{
		int previous = -1;
		int pos = 0;
		int new_col[4] = {0, 0, 0, 0};
		for (int i = 0; i < 4; i++)
		{
			deleteGridLocation(i, k);
			if (grid[i][k] != 0)
			{
				if (previous == -1)
					previous = grid[i][k];
				else
				{
					if (grid[i][k] == previous)
					{
						new_col[pos++] = 2 * previous;
						previous = -1;
					}
					else
					{
						new_col[pos++] = previous;
						previous = grid[i][k];
					}
				}
			}
		}
		if (previous != -1)
			new_col[pos] = previous;
		for (int i = 0; i < 4; i++)
		{
			if (new_col[i] == 0)
				gl.insert({i, k});
			if (new_col[i] != grid[i][k])
				effectiveMove = true;
			grid[i][k] = new_col[i];
		}
	}
	return effectiveMove;
}

bool Grid::right()
{
	bool effectiveMove = false;

	for (int i = 0; i < 4; ++i)
	{
		int previous = -1;
		int pos = 3;
		int new_row[4] = {0, 0, 0, 0};
		for (int k = 3; k >= 0; k--)
		{
			deleteGridLocation(i, k);
			if (grid[i][k] != 0)
			{
				if (previous == -1)
					previous = grid[i][k];
				else
				{
					if (grid[i][k] == previous)
					{
						new_row[pos--] = previous * 2;
						previous = -1;
					}
					else
					{
						new_row[pos--] = previous;
						previous = grid[i][k];
					}
				}
			}
		}
		if (previous != -1)
			new_row[pos] = previous;
		for (int j = 0; j < 4; j++)
		{
			if (new_row[j] == 0)
				gl.insert({i, j});
			if (new_row[j] != grid[i][j])
				effectiveMove = true;
			grid[i][j] = new_row[j];
		}
	}

	return effectiveMove;
}

bool Grid::down()
{
	bool effectiveMove = false;

	for (int k = 0; k < 4; ++k)
	{
		int previous = -1;
		int pos = 3;
		int new_col[4] = {0, 0, 0, 0};
		for (int i = 3; i >= 0; i--)
		{
			deleteGridLocation(i, k);
			if (grid[i][k] != 0)
			{
				if (previous == -1)
					previous = grid[i][k];
				else
				{
					if (grid[i][k] == previous)
					{
						new_col[pos--] = 2 * previous;
						previous = -1;
					}
					else
					{
						new_col[pos--] = previous;
						previous = grid[i][k];
					}
				}
			}
		}
		if (previous != -1)
			new_col[pos] = previous;
		for (int i = 0; i < 4; i++)
		{
			if (new_col[i] == 0)
				gl.insert({i, k});
			if (new_col[i] != grid[i][k])
				effectiveMove = true;
			grid[i][k] = new_col[i];
		}
	}

	return effectiveMove;
}