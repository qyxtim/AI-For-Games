#include "ai.h"
#include <cstdio>

int main(void)
{
    AI ai;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            scanf("%d", &ai.b(i, j));
        }
    }
    printf("Finished Reading!\n");

    if (ai.solve())
        printf("You Solve it!\n");
    else
        printf("You lose!\n");
    ai.b.output();

    return 0;
}