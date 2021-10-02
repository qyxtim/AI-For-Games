#include "board.h"
#include <cstdio>
#include <cstring>

Board::Board(char c) : whoFirst(c)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            availableActions.insert({i, j});
}

Board::Board(const Board &other) : availableActions(other.availableActions), currentPlay(other.currentPlay), whoFirst(other.whoFirst)
{
    memcpy(board, other.board, sizeof(board));
}

void Board::output() const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == -1)
                printf("  ");
            else if (board[i][j] == 0)
                printf("o ");
            else if (board[i][j] == 1)
                printf("x ");
        }
        printf("\n");
    }
}

bool Board::move(GridLocation location)
{
    if (availableActions.find(location) == availableActions.end())
        return false;
    availableActions.erase(location);
    board[location.x][location.y] = currentPlay;

    currentPlay = !currentPlay;
    return true;
}

bool Board::isEnd() const
{
    if (availableActions.size() == 0)
        return true;

    // Check Row
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == -1)
            continue;
        bool same = true;
        for (int j = 1; j < 3; j++)
        {
            if (board[i][j] != board[i][0])
                same = false;
        }
        if (same)
            return same;
    }

    // Check Col
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == -1)
            continue;
        bool same = true;
        for (int j = 1; j < 3; j++)
        {
            if (board[j][i] != board[0][i])
                same = false;
        }
        if (same)
            return same;
    }

    // Check diagonal
    if (board[0][0] != -1 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;
    if (board[0][2] != -1 && board[0][2] == board[1][1] && board[2][0] == board[1][1])
        return true;

    return false;
}

int Board::winnerHelper() const
{
    // Check Row
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == -1)
            continue;
        bool same = true;
        for (int j = 1; j < 3; j++)
        {
            if (board[i][j] != board[i][0])
                same = false;
        }
        if (same)
            return board[i][0];
    }

    // Check Col
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == -1)
            continue;
        bool same = true;
        for (int j = 1; j < 3; j++)
        {
            if (board[j][i] != board[0][i])
                same = false;
        }
        if (same)
            return board[0][i];
    }

    // Check diagonal
    if (board[0][0] != -1 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[1][1];
    if (board[0][2] != -1 && board[0][2] == board[1][1] && board[2][0] == board[1][1])
        return board[1][1];

    return 2;
}

int Board::winner() const
{
    int win = winnerHelper();
    if (win == 0)
    {
        // If o is the winning symbol and you choose to be first player, you lose
        if (whoFirst == '0')
            return -1;
        else
            return 1;
    }
    else if (win == 1)
    {
        // If x is the winning symbol and you choose to be first player, you won
        if (whoFirst == '0')
            return 1;
        else
            return -1;
    }
    else
        return 0;
}