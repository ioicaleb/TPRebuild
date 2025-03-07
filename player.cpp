#include <chrono>
#include "dialogue.h"

class Player {
private:
	int sugar_level = 0;
	int experience = 0;
	int licks = 0;
	double critical_threshold = 0.95;
	int critical_multiplier = 1;

public:
	int get_sugar_level() { return sugar_level; };
	int get_experience() { return experience; };
	int get_licks() { return licks; };

	void increment_sugar() { ++sugar_level; };
	void increment_exp() { ++experience; };
	void remove_exp() { experience -= 10; };
	void increment_licks() { ++licks; };

	void lower_critical_threshold() { critical_threshold = 0.85; };
	void increase_critical_multiplier() { critical_multiplier = 3; };

	int set_sugar(int change) {
		if (sugar_level >= change) {
			sugar_level -= change;
			return 0;
		}
		else {
			return change - sugar_level;
		}
	};

	int roll_damage() {
		int crit_damage = 0;
		srand(time(NULL));
		if ((rand() % 101) > critical_threshold) {
			crit_damage = (rand() % 11 + 1) * critical_multiplier;
			print_line("Chomp!");
		}
		return crit_damage;
	};

	void eat_candy() {
		print_line("Mmmmm... You've reached the delicious Tootsie Pop center!\n Your sugar level is at " + std::to_string(sugar_level) + ".");
		if (sugar_level > 50) {
			print_line("Careful! If your sugar level reaches 100, you'll crash! Try drinking some water!");
		};
		increment_exp();
		print_line("You now have " + std::to_string(experience) + " lolipop stick" + (experience > 1 ? "s" : "") + "!");
	};
};