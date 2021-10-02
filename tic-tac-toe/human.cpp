#include "board.h"
#include <cstdio>
#include <string>

using namespace std;
using namespace std::string_literals;

int main(void)
{
    char c;

    const char *s = R"(Welcome to Tic Tac Toe!
    You can input (x, y) coordinates in the terminal to play with AI
    Please choose who start first: 0 for x, 1 for o:)";

    printf("%s\n", s);
    scanf("%c", &c);

    Board b(c);
    int x, y;
    while (!b.isEnd())
    {
        printf("Select Your Choice now: \n");

        do
        {
            scanf("%d %d", &x, &y);
        } while (!b.move({x, y}));

        b.output();
    }

    int winner = b.winner();
    if (winner == 0)
        printf("Tie!\n");
    else if (winner == 1)
        printf("You won!\n");
    else
        printf("You lose!\n");

    return 0;
}