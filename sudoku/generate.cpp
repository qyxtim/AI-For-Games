#include "ai.h"
#include <random>
#include <set>

int main(void)
{
    srand(unsigned(time(NULL)));

    AI ai;
    Board b;

    do
    {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                ai.b(i, j) = 0;

        ai.build();

        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                b(i, j) = ai.b(i, j);
    } while (!ai.solve());

    b.output();

    return 0;
}