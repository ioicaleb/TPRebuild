#include "dialogue.h"

class Enemy {
private:
	const std::string Flavors[5] = { "cherry", "chocolate", "orange", "grape", "raspberry" };

public:
	std::string Name;
	int Health = 0;

	Enemy() {
		srand(time(NULL));
		Name = Flavors[rand() % 5];
		Health = 10;
		std::string introduction = "Oh, no! " + Dialogue::capitalize(Dialogue::set_article(Name)) + Name + " pop has appeared!";
		Dialogue::print_line(introduction);
	};

	Enemy(const char* name) {
		Name = name;
		std::string introduction = "";
		if (name == "Bishop") {
			Health = 20;
			introduction = "Oh, no! It's the Bishop!";
		}
		else if (name == "Knight") {
			Health = 40;
			introduction = "Oh, no! It's the Knight!";
		}
		else if (name == "Rook") {
			Health = 60;
			introduction = "Oh, no! It's the Rook!";
		}
		else if (name == "King") {
			Health = 180;
			introduction = "The legends are true...\nIt's the King!";
		}
		Dialogue::print_line(introduction);
	};

	Enemy(bool skip) {};
};
