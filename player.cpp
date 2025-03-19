#include <time.h>
#include <stdlib.h>
#include "dialogue.h"

struct Player {
	int Sugar_level = 0;
	int Experience = 0;
	int Licks = 0;
	int Critical_threshold = 95;
	int Critical_multiplier = 1;

	int get_sugar_level() { return Sugar_level; };
	int get_experience() { return Experience; };
	int get_licks() { return Licks; };

	void increment_sugar() { ++Sugar_level; };
	void increment_exp() { ++Experience; };
	void remove_exp() { Experience -= 10; };
	void increment_licks() { ++Licks; };

	void lower_critical_threshold() { Critical_threshold = 85; };
	void increase_critical_multiplier() { Critical_multiplier = 2; };

	int set_sugar(int change) {
		if (Sugar_level >= change) {
			Sugar_level -= change;
			return 0;
		}
		else {
			return change - Sugar_level;
		}
	};

	int roll_damage() {
		int crit_damage = 1;
		srand(time(NULL));
		if ((rand() % 101) > Critical_threshold) {
			crit_damage += (rand() % 11) * Critical_multiplier;
			Dialogue::print_line("Chomp!");
		}
		return crit_damage;
	};

	void eat_candy() {
		Dialogue::print_line("Mmmmm... You've reached the delicious Tootsie Pop center!\nYour sugar level is at " + std::to_string(Sugar_level) + ".");
		if (Sugar_level > 50) {
			Dialogue::print_line("Careful! If your sugar level reaches 100, you'll crash! Try drinking some water!");
		};
		increment_exp();
		Dialogue::print_line("You now have " + std::to_string(Experience) + " lolipop stick" + (Experience > 1 ? "s" : "") + "!");
	};
};
