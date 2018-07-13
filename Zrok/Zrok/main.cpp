#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "world.h"
#include "comunicate.h"

using namespace std;

#define BACKSPACE "\033[D\033[K"
#define WHITE_ "\033[1;36m"
#define _WHITE "\033[0m"


int main()
{
	string player_input;
	vector<string> args;
	bool content = false;
	args.reserve(10);

	cout << WHITE_ "Welcome to MyZork!\n" _WHITE;
	cout << "----------------\n";

	World my_world;

	args.push_back("look");

	while (1)
	{
 		while (content)
		{
			getline(cin, player_input);
			Tokenize(player_input, args);
			content = false;
		}

		if (args.size() > 0 && Same(args[0], "quit"))
			break;

		if (my_world.Tick(args) == false)
			cout << "\nSorry, I do not understand your command.\n";

		if (args.size() > 0)
		{
			args.clear();
			player_input = "";
			cout << "\n>";
		}
		content = true;
	}

	cout << "\nThanks for playing, Bye!\n";
	return 0;
}

