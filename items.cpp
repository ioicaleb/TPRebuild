#include "dialogue.h"
#include "items.h"

std::string Name;
std::string Description;

Items::Items() = default;

Items::Items(std::string name, std::string description) {
	Name = name;
	Description = description;
};

void Items::get_item() {
	if (Collections::verify_inventory(Name)) {
		Dialogue::print_line("You already have one. CHECK your TOOLBELT.");
	}
	else
	{
		Collections::add_inventory(this);
		Dialogue::print_line("You strap the " + Name + " to your TOOLBELT.");
	}
};
