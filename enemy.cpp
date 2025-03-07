#include "dialogue.h"
#include <random>

class Enemy {
public:
	Enemy() {
		srand(time(NULL));
		Name = Flavors[rand() % 5];
		Health = 10;
		print_line(introduction);
	};

	Enemy(std::string name) {
		Name = name;
		if(name == "Bishop") {
			Health = 20;
			introduction = "Oh, no! It's the Bishop!";
		}
		else if(name == "Knight") {
			Health = 40;
			introduction = "Oh, no! It's the Bishop!";
		}
		else if (name == "Rook") {
			Health = 60;
			introduction = "Oh, no! It's the Bishop!";
		}
		else if (name == "King") {
			Health = 180;
			introduction = "The legends are true...\n It's the King!";
		}
		print_line(introduction);
	};

	std::string Name;
	int Health;
	std::string introduction = "Oh, no!A" + Name == "orange" ? "n " : " " + Name + " pop has appeared!";

private:
	const std::string Flavors[5] = { "cherry", "chocolate", "orange", "grape", "raspberry" };
};