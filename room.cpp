#include "room_handler.h"

Room::Room(std::string name, std::string description, double encounter_chance, std::set<std::string> get_items, std::set<std::string> interactable_items, std::set<std::string> useable_items) {
	Name = name;
	Description = description;
	Encounter_chance = encounter_chance;
	Room_Handler::Map.add_get_item(Name, get_items);
	Room_Handler::Map.add_interactable(Name, interactable_items);
	Room_Handler::Map.add_use_item(Name, useable_items);
};

bool Room::roll_encounter() {
	if (Name == "Basement") {
		return true;
	}
	else if (Name == "Attic") {
		return true;
	}
	else if (Name == "Garage") {
		return true;
	}
	else if (Name == "Hidden Room") {
		return true;
	}
	return (Encounter_chance * (rand() % 101)) > 30;
};
