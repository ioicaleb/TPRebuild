#include "dialogue.h"

class Items{
public:
	std::string name;
	std::string description;

	void get_item() { print_line("You strap the " + name + " to your toolbelt."); };
	void get_item(std::string message) { print_line(message); };

	void use_item();
	void use_item(std::string message) { print_line(message); };
};
