#include "dialogue.h"

class Interactable {
public:
	std::string name;
	std::string description;

	void use_interactable() { print_line("There's nothing useful you can do with the " + name + "."); };
	void use_interactable(std::string message) { print_line(message); };
};