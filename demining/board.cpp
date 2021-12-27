#include "board.h"

#include <cstdio>
#include <random>

Board::Board(int s) : size(s), taggedLocations({}), clickedLocations({})
{
    grid = new int *[size];
    for (int i = 0; i < size; i++)
    {
        grid[i] = new int[size];
        for (int j = 0; j < size; j++)
            grid[i][j] = 0;
    }

    int numberOfMines = 0;
    while (numberOfMines < (int)(factor * size * size))
    {
        int x = rand() % size, y = rand() % size;
        if (grid[x][y] != -1)
        {
            numberOfMines++;
            grid[x][y] = -1;

            if (x > 0 && grid[x - 1][y] != -1)
                grid[x - 1][y]++;
            if (x > 0 && y > 0 && grid[x - 1][y - 1] != -1)
                grid[x - 1][y - 1]++;
            if (x > 0 && y < size - 1 && grid[x - 1][y + 1] != -1)
                grid[x - 1][y + 1]++;
            if (y > 0 && grid[x][y - 1] != -1)
                grid[x][y - 1]++;
            if (y < size - 1 && grid[x][y + 1] != -1)
                grid[x][y + 1]++;
            if (x < size - 1 && grid[x + 1][y] != -1)
                grid[x + 1][y]++;
            if (x < size - 1 && y > 0 && grid[x + 1][y - 1] != -1)
                grid[x + 1][y - 1]++;
            if (x < size - 1 && y < size - 1 && grid[x + 1][y + 1] != -1)
                grid[x + 1][y + 1]++;
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < size; i++)
        delete[] grid[i];
    delete[] grid;
}

void Board::finaloutput() const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (grid[i][j] == -1)
                printf("o");
            else
                printf("%d", grid[i][j]);
            printf(" ");
        }
        printf("\n");
    }
}

void Board::output() const
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (taggedLocations.find({i, j}) != taggedLocations.end())
                printf("△");
            else if (clickedLocations.find({i, j}) != clickedLocations.end())
                printf("%d", grid[i][j]);
            else
                printf("☐");
            printf(" ");
        }
        printf("\n");
    }
}

void Board::tag(const GridLocation& location)
{
    taggedLocations.insert(location);
}

void Board::reset(const GridLocation& location)
{
    taggedLocations.erase(location);
}

void Board::click(const GridLocation& location)
{
    if (taggedLocations.find(location) != taggedLocations.end())
        return;
    // if a mine is clicked, taggedLocations and clickedLocations will both insert this location
    mineLoc = location;
    clickedLocations.insert(location);
}

bool Board::clickMine() const{
    return mineLoc.x != -1 && mineLoc.y != -1;
}

bool Board::isEnd() const
{
    return clickMine() || int(size * size * factor) + clickedLocations.size() == size * size;
}

int Board::getMines(const GridLocation& location) const
{
    return grid[location.x][location.y];
}
