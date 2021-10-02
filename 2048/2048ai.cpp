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
        // For user control
        // getchar();
    }

    return 0;
}