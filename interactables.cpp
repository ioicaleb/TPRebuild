#include "interactables.h"

std::string Name;
std::string Description;

Interactables::Interactables(std::string name, std::string description) {
	Name = name;
	Description = description;
};

void Interactables::use_interactable() const { Dialogue::print_line("There's nothing useful you can do with the " + Name + "."); };
void Interactables::use_interactable(std::string message) { Dialogue::print_line(message); };
