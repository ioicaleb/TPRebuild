#include "characters_handler.h"
#include "game_manager.h"
#include "dialogue.h"
#include "collections.h"

Enemy* lolipop;

void Characters_Handler::spawn_enemy(const std::string& roomname) {
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

bool Characters_Handler::attack_enemy(bool* combat) {
	if (!*combat) {
		Dialogue::print_line("Save your licks for the candies.");
		return false;
	}
	else {
		player.increment_licks();
		int damage = player.roll_damage();
		Dialogue::print_line("You managed to get " + std::to_string(damage) + " licks!");
		lolipop->Health -= damage;
		if (lolipop->Health < 1) {
			if (lolipop->Name == "Bishop") {
				Collections::get_room("Garage")->defeat_boss();
			}
			if (lolipop->Name == "Knight") {
				Collections::get_room("Attic")->defeat_boss();
			}
			if (lolipop->Name == "Rook") {
				Collections::get_room("Basement")->defeat_boss();
			}
			if (lolipop->Name == "King") {
				Collections::get_room("Hidden Room")->defeat_boss();
			}

			player.eat_candy();

			if (player.get_sugar_level() > 99) {
				Game_Manager::lose_game();
			}

			return false;
		}
		return true;
	};
};

bool Characters_Handler::attack_boss(const std::string& message) {
	lolipop->Health = 0;
	Dialogue::print_line(message);
	return true;
};

bool Characters_Handler::attack_boss(int damage) {
	std::string message = lolipop->Health >= damage ? "The King still appears stoic and daunting." : "The king is nothing more than a fragile shell now.";
	Dialogue::print_line(message);
	return true;
};
