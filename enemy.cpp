#include "dialogue.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

using namespace std;

class Enemy {
private:
	const string Flavors[5] = { "cherry", "chocolate", "orange", "grape", "raspberry" };

public:
	string Name;
	int Health = 0;
	string Introduction = "Oh, no!A" + Name == "orange" ? "n " : " " + Name + " pop has appeared!";

	Enemy() {
		srand(time(NULL));
		Name = Flavors[rand() % 5];
		Health = 10;
		Dialogue::print_line(Introduction);
	};

	Enemy(string name) {
		Name = name;
		if (name == "Bishop") {
			Health = 20;
			Introduction = "Oh, no! It's the Bishop!";
		}
		else if (name == "Knight") {
			Health = 40;
			Introduction = "Oh, no! It's the Bishop!";
		}
		else if (name == "Rook") {
			Health = 60;
			Introduction = "Oh, no! It's the Bishop!";
		}
		else if (name == "King") {
			Health = 180;
			Introduction = "The legends are true...\n It's the King!";
		}
		Dialogue::print_line(Introduction);
	};
};
