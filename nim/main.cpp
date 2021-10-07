#include "ai.h"
#include <cstdio>
#include <random>

int main(void)
{
    srand((unsigned)(time(NULL)));

    int piles;
    int player;
    int x, y;

    const char *s = R"(Welcome to Nim!
    You need to decide how many piles do you want to have. Input a number:)";

    printf("%s\n", s);

    do
    {
        scanf("%d", &piles);
    } while (piles <= 0);

    const char *s2 = "Now, please choose who start first: 0 for you, 1 for AI:";
    printf("%s\n", s2);

    do
    {
        scanf("%d", &player);
    } while (player != 0 && player != 1);

    AI ai(piles, player);

    printf("Now AI is training itself. Please wait...\n");
    ai.train();
    printf("\nAI finished training. If you want to take y from position x, please input (x, y).\n");

    while (!ai.m.isEnd())
    {
        ai.m.output();
        if (player == 0)
        {
            printf("\nYour turn:\n");
            do
            {
                scanf("%d %d", &x, &y);
            } while (!ai.m.remove({x, y}));
        }
        else
        {
            printf("AI makes a move!\n");
            ai.move();
        }
        player = !player;
        printf("\n");
    }

    if (ai.m.winner() == 0)
        printf("You won!\n");
    else
        printf("You lost!\n");

    return 0;
}