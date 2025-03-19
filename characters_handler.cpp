#include "characters_handler.h"
#include "enemy.cpp"

Enemy* lolipop = new Enemy(false);
Player player = Player();

Player& Characters_Handler::get_player() {
	return player;
};

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

bool Characters_Handler::attack_enemy(bool& combat) {
	if (!combat) {
		Dialogue::print_line("Save your licks for the candies.");
		return false;
	}
	else {
		player.increment_licks();
		player.increment_sugar();
		int damage = player.roll_damage();
		Dialogue::print_line("You managed to get " + std::to_string(damage) + " lick" + (damage > 1 ? "s!" : "!"));
		lolipop->Health -= damage;
		if (lolipop->Health < 1) {
			if (lolipop->Name == "Bishop") {
				Room_Handler::Map.defeat_boss("Garage");
			}
			else if (lolipop->Name == "Knight") {
				Room_Handler::Map.defeat_boss("Attic");
			}
			else if (lolipop->Name == "Rook") {
				Room_Handler::Map.defeat_boss("Basement");
			}
			else if (lolipop->Name == "King") {
				Room_Handler::Map.defeat_boss("Hidden Room");
			}

			player.eat_candy();

			return false;
		}
		return true;
	};
};

void Characters_Handler::attack_boss() {
	lolipop->Health = 0;
};

void Characters_Handler::attack_boss(int damage) {
	std::string message = lolipop->Health >= damage ? "The King still appears stoic and daunting." : "The king is nothing more than a fragile shell now.";
	Dialogue::print_line(message);
};
