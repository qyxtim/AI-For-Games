#include "2048grid.h"
#include <cstdio>
#include <string>

void getInput(Grid &g)
{
	char ch = getchar();
	while (ch != 'w' && ch != 'W' && ch != 'a' && ch != 'A' && ch != 's' && ch != 'S' && ch != 'd' && ch != 'D')
	{
		ch = getchar();
	}

	bool isSuccess = true;
	if (ch == 'w' || ch == 'W')
	{
		isSuccess = g.up();
	}
	else if (ch == 'a' || ch == 'A')
	{
		isSuccess = g.left();
	}
	else if (ch == 's' || ch == 'S')
	{
		isSuccess = g.down();
	}
	else if (ch == 'd' || ch == 'D')
	{
		isSuccess = g.right();
	}

	if (isSuccess)
		g.generateAPlace();
}

int main()
{
	using namespace std::string_literals;
	srand((unsigned)time(NULL));

	Grid g;
	const char *welcome = R"(Welcome to 2048, a game based on cpp console. Hope you can have an enjoyable experience here.
	You can press WASD to control and Ctrl-C to end the game.)";

	while (true)
	{

		printf("%s\n", welcome);
		g.structure();
		getInput(g);
		printf("\n");
	}
}
