#include "characters.h"
#include "game_manager.h"
#include "dialogue.h"
#include <algorithm>
#include "enemy.cpp"
#include "player.cpp"

Enemy* lolipop;
Player player;

void spawn_enemy(std::string roomname) {
	if (roomname == "Garage") {
		lolipop = new Enemy("Bishop");
	}
	else if (roomname == "Basement") {
		lolipop = new Enemy("Rook");
	}
	else if (roomname == "Attic") {
		lolipop = new Enemy("Knight");
	}
	else if (roomname == "Hidden Room") {
		lolipop = new Enemy("King");
	}
	else {
		lolipop = new Enemy();
	}
};

bool attack_enemy(bool combat) {
	if (!combat) {
		print_line("Save your licks for the candies.");
		return false;
	}
	else {
		player.increment_licks();
		int damage = player.roll_damage();
		print_line("You managed to get " + std::to_string(damage) + " licks!");
		lolipop->Health -= damage;
		if (lolipop->Health < 1) {
			if (lolipop->Name == "Bishop") {
				garage.defeat_boss();
			}
			if (lolipop->Name == "Knight") {
				attic.defeat_boss();
			}
			if (lolipop->Name == "Rook") {
				basement.defeat_boss();
			}
			if (lolipop->Name == "King") {
				hidden_room.defeat_boss();
			}

			player.eat_candy();

			if (player.get_sugar_level() > 99) {
				lose_game();
			}
		}
		return true;
	};
};

bool attack_boss(std::string message) {
	lolipop->Health = 0;
	print_line(message);
	return true;
};

bool attack_boss(int damage) {
	std::string message = lolipop->Health >= damage ? "The King still appears stoic and daunting." : "The king is nothing more than a fragile shell now.";
	print_line(message);
};
