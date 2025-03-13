#include "room.h"

double Encounter_chance = 0.0;

void Room::add_gettable_item(std::set<std::string> items) {
	for (std::string item : items) {
		Get_items.insert(item);
	}
};

void Room::add_useable_item(std::set<std::string> items) {
	for (std::string item : items) {
		Usable_items.insert(item);
	}
};

void Room::add_interactable(std::set<std::string> items) {
	for (std::string item : items) {
		Room_interactables.insert(item);
	};
};

Room::Room(std::string name, std::string description, double encounter_chance, std::set<std::string> getItems, std::set<std::string> interactables) {
	Name = name;
	Description = description;
	Encounter_chance = encounter_chance;
	add_gettable_item(getItems);
	add_interactable(interactables);
	if (Name == "Attic") {
		Locked = true;
		auto defeat_boss = [this]() {
			Boss_defeated = true;
			std::string message = "You see the small gilded CHEST your grandmother bequeathed you, just as you left it.\nYour camping LANTERN rests on some boxes of halloween decorations.";
			Get_items.insert("lantern");
			Room_interactables.insert("chest");
			return message;
			};
	}
	else if (Name == "Basement") {
		Locked = true;
		auto defeat_boss = [this]() {
			Boss_defeated = true;
			std::string message = "The pale glow of the lantern illuminates the FURNACE and the WATER MAIN.\n On a wall rack, you see your METAL DETECTOR and SHOVEL.";
			Description = Description.substr(0, Description.find("\n")) + "\n" + message;
			return message;
			};
	}
	else if (Name == "Garage") {
		Locked = true;
		auto defeat_boss = [this]() {
			Boss_defeated = true;
			std::string message = "";
			Description += " " + message;
			return message;
			};
	}
	else if (Name == "Hidden Room") {
		auto defeat_boss = [this]() {
			Boss_defeated = true;
			std::string message = "";
			return message;
			};
	}

};

bool Room::roll_encounter() { return (Encounter_chance * (rand() % 101)) > 30; };
