#include "board.h"
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

    Board b(size);

    const char *message = R"(If you want to click a plce, enter 0 x y
    If you want to tage a place as mine, enter 1 x y
    Revert tagging, enter 2 x y.)";
    printf("%s\n\n", message);

    int instruction = -1, x = -1, y = -1;
    while (!b.isEnd())
    {
        b.output();
        printf("\n");

        do
        {
            scanf("%d %d %d", &instruction, &x, &y);
        } while ((instruction != 0 && instruction != 1 && instruction != 2) && (x >= size) && (y >= size) && (x < 0) && (y < 0));

        if (instruction == 0)
            b.click({x, y});
        else if (instruction == 1)
            b.tag({x, y});
        else
            b.reset({x, y});

        printf("\n");
    }

    std::set<GridLocation> intersect = b.intersections();
    if (intersect.size() != 0)
    {
        printf("You lose!\n");
        printf("The mine is at coordinate (%d, %d)\n", intersect.begin()->x, intersect.begin()->y);
    }
    else
        printf("You won!\n");
    b.finaloutput();

    return 0;
}