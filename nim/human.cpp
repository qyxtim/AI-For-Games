#include "board.h"
#include <cstdio>
#include <random>

int main(void)
{
    srand(unsigned(time(NULL)));

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

    const char *s2 = "Now, please choose who start first: 0 for Player 0, 1 for Player 1:";
    printf("%s\n", s2);

    do
    {
        scanf("%d", &player);
    } while (player != 0 && player != 1);

    Nim n(piles, player);
    printf("If you want to take y from position x, please input (x, y):\n");
    while (!n.isEnd())
    {
        n.output();
        scanf("%d %d", &x, &y);
        n.remove({x, y});
    }

    if (n.winner() == player)
        printf("The player you choose won!\n");
    else
        printf("The player you choose lost!\n");

    return 0;
}