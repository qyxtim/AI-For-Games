#include "ai.h"
#include <cstdio>
#include <random>

int main(void)
{
    using namespace std::string_literals;
    srand(unsigned(time(NULL)));

    const char *welcome = R"(Welcome to demining game!
    Please input the size of the n by n game(input n):)";

    printf("%s\n", welcome);
    int size = 0;
    scanf("%d", &size);
    getchar();

    AI ai(size);
    ai.b.output();

    char c;
    while (!ai.b.isEnd())
    {
        printf("Press any key to continue...\n");
        scanf("%c", &c);
        ai.move();
        ai.b.output();
    }

    if (ai.b.clickMine())
    {
        printf("\nYou lose!\n");
        printf("The mine is at coordinate (%d, %d)\n", ai.b.mineLoc.x, ai.b.mineLoc.y);
    }
    else
        printf("\nYou won!\n");

    ai.b.finaloutput();

    return 0;
}