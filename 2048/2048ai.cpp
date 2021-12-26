#include "ai.h"
#include <cstdio>
#include <random>

int main(void)
{
    srand((unsigned)time(NULL));

    AI ai = AI();

    ai.g.structure();
    while (ai.makeMove())
    {
        ai.g.generateAPlace();
        ai.g.structure();
    }

    return 0;
}