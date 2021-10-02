#include "ai.h"
#include <cstdio>
#include <string>

int main(void)
{
    using namespace std::string_literals;

    const char *s = R"(Welcome to Tic Tac Toe!
    You can input (x, y) coordinates in the terminal to play with AI
    Please choose who start first: 0 for you, 1 for AI:)";

    printf("%s\n", s);

    char c;
    scanf("%c", &c);
    ;

    AI ai(c);

    int x, y;
    bool isAINow = c == '1' ? true : false;

    while (!ai.b.isEnd())
    {
        if (isAINow)
        {
            ai.move();
            ai.b.output();
        }
        else
        {
            printf("Select Your Choice now: \n");
            do
            {
                scanf("%d %d", &x, &y);
            } while (!ai.b.move({x, y}));
        }
        isAINow = !isAINow;
    }

    int winner = ai.b.winner();
    if (winner == 0)
        printf("Tie!\n");
    else if (winner == 1)
        printf("You won!\n");
    else
        printf("You lose!\n");

    return 0;
}