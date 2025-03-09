#include "room.h"
#include <set>
#include <string>

using namespace std;

string Description;
double Encounter_chance;

void Room::add_gettable_item(set<string> items) {
	for (string item : items) {
		Get_items.insert(item);
	}
};

void Room::add_useable_item(set<string> items) {
	for (string item : items) {
		Usable_items.insert(item);
	}
};

void Room::add_interactable(set<string> items) {
	for (string item : items) {
		Room_interactables.insert(item);
	};
};

Room::Room() = default;
Room::Room(string name, string description, double encounter_chance, set<string> getItems, set<string> interactables) {
	Name = name;
	Description = description;
	Encounter_chance = encounter_chance;
	add_gettable_item(getItems);
	add_interactable(interactables);
	if (name == "Attic") {
		Locked = true;
		auto defeat_boss = [this]() {
			Boss_defeated = true;
			};
	}
	else if (name == "Garage") {
		Locked = true;
		auto defeat_boss = [this]() {
			Boss_defeated = true;
			};
	}
	else if (name == "Basement") {
		Locked = true;
		auto defeat_boss = [this]() {
			Boss_defeated = true;
			};
	}
	else if (name == "Hidden Room") {
		auto defeat_boss = [this]() {
			Boss_defeated = true;
			};
	}
};

bool Room::roll_encounter() { return (Encounter_chance * (rand() % 101)) > 30; };
