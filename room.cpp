#include "room_handler.h"

Room::Room(std::string name, std::string description, double encounter_chance, std::set<std::string> get_items, std::set<std::string> interactable_items, std::set<std::string> useable_items) {
	Name = name;
	Description = description;
	Encounter_chance = encounter_chance;
	for (std::string item : get_items) {
		Get_items.insert(item);
	}
	for (std::string item : interactable_items) {
		Interactables.insert(item);
	}
	for (std::string item : useable_items) {
		Useable_items.insert(item);
	}
};

bool Room::roll_encounter() {
	if (Name == "Basement" || Name == "Attic" || Name == "Garage" || Name == "Hidden Room") {
		return !Room_Handler::Map.verify_boss(Name) && !Room_Handler::Map.verify_locked(Name);
	}
	return (Encounter_chance * (rand() % 101)) > 30;
};
