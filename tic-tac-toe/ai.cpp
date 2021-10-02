#include "ai.h"

AI::AI(char c) : b(c) {}

int AI::min(Board b)
{
    if (b.isEnd())
        return b.winner();

    int score = 2;
    for (auto iter = b.availableActions.begin(); iter != b.availableActions.end(); iter++)
    {
        if (score == -1)
            return score;
        Board tmp = b;
        tmp.move(*iter);
        int tmpScore = max(tmp);
        score = tmpScore < score ? tmpScore : score;
    }

    return score;
}

int AI::max(Board b)
{
    if (b.isEnd())
        return b.winner();

    int score = -2;
    for (auto iter = b.availableActions.begin(); iter != b.availableActions.end(); iter++)
    {
        if (score == 1)
            return score;
        Board tmp = b;
        tmp.move(*iter);
        int tmpScore = min(tmp);
        score = tmpScore > score ? tmpScore : score;
    }

    return score;
}

GridLocation AI::minimax()
{
    // Iterate through all the possible actions
    GridLocation bestChoice;
    int score = 2;
    for (auto iter = b.availableActions.begin(); iter != b.availableActions.end(); iter++)
    {
        if (score == -1)
            return bestChoice;
        Board tmp = b;
        tmp.move(*iter);
        int tmpScore = max(tmp);

        if (tmpScore < score)
        {
            score = tmpScore;
            bestChoice = *iter;
        }
    }

    return bestChoice;
}

void AI::move()
{
    b.move(minimax());
}