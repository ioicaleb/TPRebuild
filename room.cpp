#include "room.h"

double Encounter_chance = 0.0;

void Room::add_gettable_item(std::set<std::string> items) {
	for (std::string item : items) {
		Get_items.insert(item);
	}
};

void Room::add_useable_item(std::string item) {
	Usable_items.insert(item);
};

void Room::remove_useable_item(std::string item) {
	Usable_items.erase(item);
};

void Room::add_useable_item(std::set<std::string> items) {
	for (std::string item : items) {
		Usable_items.insert(item);
	}
};

void Room::add_interactable(std::set<std::string> items) {
	for (std::string item : items) {
		Room::Room_interactables.insert(item);
	};
};

bool Room::verify_item(std::string item) {
	if (Usable_items.find(item) != Usable_items.end()) {
		return true;
	}
	if (Room_interactables.find(item) != Room_interactables.end()) {
		return true;
	}
	return false;
};

void Room::unlock_room() { Locked = false; }

void Room::defeat_boss() { Boss_defeated = true; }

Room::Room(std::string name, std::string description, double encounter_chance, std::set<std::string> getItems, std::set<std::string> interactables) {
	Name = name;
	Description = description;
	Encounter_chance = encounter_chance;
	add_gettable_item(getItems);
	add_interactable(interactables);
	if (Name == "Attic") {
		Locked = true;
		Boss_defeated = false;
	}
	else if (Name == "Basement") {
		Locked = true;
		Boss_defeated = false;
	}
	else if (Name == "Garage") {
		Locked = true;
		Boss_defeated = false;
	}
	else if (Name == "Hidden Room") {
		Boss_defeated = false;
	}
};

bool Room::roll_encounter() { 
	if (Name == "Basement" || Name == "Attic" || Name == "Garage" || Name == "Hidden Room") { return !Locked && !Boss_defeated; }
	return (Encounter_chance * (rand() % 101)) > 30; 
};
